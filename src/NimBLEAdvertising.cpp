/*
 * NimBLEAdvertising.cpp
 *
 *  Created: on March 3, 2020
 *      Author H2zero
 * 
 * Originally:
 *
 * BLEAdvertising.cpp
 *
 * This class encapsulates advertising a BLE Server.
 *  Created on: Jun 21, 2017
 *      Author: kolban
 *
 */
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)
#include "services/gap/ble_svc_gap.h"
#include "NimBLEAdvertising.h"
//#include <esp_err.h>
#include "NimBLEUtils.h"
#include "NimBLELog.h"
//#include "GeneralUtils.h"

static const char* LOG_TAG = "NimBLEAdvertising";


/**
 * @brief Construct a default advertising object.
 *
 */
NimBLEAdvertising::NimBLEAdvertising() {
    memset(&m_advData, 0, sizeof m_advData);
	memset(&m_advParams, 0, sizeof m_advParams);
    const char *name = ble_svc_gap_device_name();
    
	m_advData.name                = (uint8_t *)name;
    m_advData.name_len            = strlen(name);
    m_advData.name_is_complete    = 1;
    m_advData.tx_pwr_lvl_is_present = 1;
    m_advData.tx_pwr_lvl          = BLE_HS_ADV_TX_PWR_LVL_AUTO;
    m_advData.flags               = (BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP);
	m_advData.appearance          = 0x00;
	m_advData.appearance_is_present = 0;
	m_advData.mfg_data_len    	  = 0;
	m_advData.mfg_data			  = nullptr;
	
	m_advParams.conn_mode         = BLE_GAP_CONN_MODE_UND;
    m_advParams.disc_mode         = BLE_GAP_DISC_MODE_GEN;
	m_advParams.itvl_min          = 0x20;
	m_advParams.itvl_max          = 0x40;
	
/*	m_advData.set_scan_rsp        = false;
	m_advData.manufacturer_len    = 0;
	m_advData.p_manufacturer_data = nullptr;
	m_advData.service_data_len    = 0;
	m_advData.p_service_data      = nullptr;
	m_advData.service_uuid_len    = 0;
	m_advData.p_service_uuid      = nullptr;

	m_advParams.adv_int_min       = 0x20;
	m_advParams.adv_int_max       = 0x40;
	m_advParams.adv_type          = ADV_TYPE_IND;
	m_advParams.own_addr_type     = BLE_ADDR_TYPE_PUBLIC;
	m_advParams.channel_map       = ADV_CHNL_ALL;
	m_advParams.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;
	m_advParams.peer_addr_type    = BLE_ADDR_TYPE_PUBLIC;

	m_customAdvData               = false;   // No custom advertising data
	m_customScanResponseData      = false;   // No custom scan response data
 */   
} // NimBLEAdvertising


/**
 * @brief Add a service uuid to exposed list of services.
 * @param [in] serviceUUID The UUID of the service to expose.
 */
void NimBLEAdvertising::addServiceUUID(NimBLEUUID serviceUUID) {
	m_serviceUUIDs.push_back(serviceUUID);
} // addServiceUUID


/**
 * @brief Add a service uuid to exposed list of services.
 * @param [in] serviceUUID The string representation of the service to expose.
 */
void NimBLEAdvertising::addServiceUUID(const char* serviceUUID) {
	addServiceUUID(NimBLEUUID(serviceUUID));
} // addServiceUUID


/**
 * @brief Set the device appearance in the advertising data.
 * The appearance attribute is of type 0x19.  The codes for distinct appearances can be found here:
 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.gap.appearance.xml.
 * @param [in] appearance The appearance of the device in the advertising data.
 * @return N/A.
 */
void NimBLEAdvertising::setAppearance(uint16_t appearance) {
	m_advData.appearance = appearance;
	m_advData.appearance_is_present = 1;
} // setAppearance

void NimBLEAdvertising::setMinInterval(uint16_t mininterval) {
	m_advParams.itvl_min = mininterval;
} // setMinInterval

void NimBLEAdvertising::setMaxInterval(uint16_t maxinterval) {
	m_advParams.itvl_max = maxinterval;
} // setMaxInterval
/*
void BLEAdvertising::setMinPreferred(uint16_t mininterval) {
	m_advData.min_interval = mininterval;
} // 

void BLEAdvertising::setMaxPreferred(uint16_t maxinterval) {
	m_advData.max_interval = maxinterval;
} // 
*/
void NimBLEAdvertising::setScanResponse(bool set) {
	m_scanResp = set;
}

/**
 * @brief Set the filtering for the scan filter.
 * @param [in] scanRequestWhitelistOnly If true, only allow scan requests from those on the white list.
 * @param [in] connectWhitelistOnly If true, only allow connections from those on the white list.
 */
 /*
void BLEAdvertising::setScanFilter(bool scanRequestWhitelistOnly, bool connectWhitelistOnly) {
	ESP_LOGD(LOG_TAG, ">> setScanFilter: scanRequestWhitelistOnly: %d, connectWhitelistOnly: %d", scanRequestWhitelistOnly, connectWhitelistOnly);
	if (!scanRequestWhitelistOnly && !connectWhitelistOnly) {
		m_advParams.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;
		ESP_LOGD(LOG_TAG, "<< setScanFilter");
		return;
	}
	if (scanRequestWhitelistOnly && !connectWhitelistOnly) {
		m_advParams.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY;
		ESP_LOGD(LOG_TAG, "<< setScanFilter");
		return;
	}
	if (!scanRequestWhitelistOnly && connectWhitelistOnly) {
		m_advParams.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST;
		ESP_LOGD(LOG_TAG, "<< setScanFilter");
		return;
	}
	if (scanRequestWhitelistOnly && connectWhitelistOnly) {
		m_advParams.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST;
		ESP_LOGD(LOG_TAG, "<< setScanFilter");
		return;
	}
} // setScanFilter
*/

/**
 * @brief Set the advertisement data that is to be published in a regular advertisement.
 * @param [in] advertisementData The data to be advertised.
 */
 
void NimBLEAdvertising::setAdvertisementData(NimBLEAdvertisementData& advertisementData) {
	NIMBLE_LOGD(LOG_TAG, ">> setAdvertisementData");
	int rc = ble_gap_adv_set_data(
		(uint8_t*)advertisementData.getPayload().data(),
		advertisementData.getPayload().length());
	if (rc != 0) {
		NIMBLE_LOGE(LOG_TAG, "ble_gap_adv_set_data: %d %s", rc, NimBLEUtils::returnCodeToString(rc));
	}
	m_customAdvData = true;   // Set the flag that indicates we are using custom advertising data.
	NIMBLE_LOGD(LOG_TAG, "<< setAdvertisementData");
} // setAdvertisementData


/**
 * @brief Set the advertisement data that is to be published in a scan response.
 * @param [in] advertisementData The data to be advertised.
 */
 /*
void BLEAdvertising::setScanResponseData(BLEAdvertisementData& advertisementData) {
	ESP_LOGD(LOG_TAG, ">> setScanResponseData");
	esp_err_t errRc = ::esp_ble_gap_config_scan_rsp_data_raw(
		(uint8_t*)advertisementData.getPayload().data(),
		advertisementData.getPayload().length());
	if (errRc != ESP_OK) {
		ESP_LOGE(LOG_TAG, "esp_ble_gap_config_scan_rsp_data_raw: %d %s", errRc, GeneralUtils::errorToString(errRc));
	}
	m_customScanResponseData = true;   // Set the flag that indicates we are using custom scan response data.
	ESP_LOGD(LOG_TAG, "<< setScanResponseData");
} // setScanResponseData
*/
/**
 * @brief Start advertising.
 * Start advertising.
 * @return N/A.
 */
void NimBLEAdvertising::start() {
	NIMBLE_LOGD(LOG_TAG, ">> Advertising start: customAdvData: %d, customScanResponseData: %d", m_customAdvData, m_customScanResponseData);
	ble_uuid16_t* uuids16 = nullptr;
	ble_uuid32_t* uuids32 = nullptr;
	ble_uuid128_t* uuids128 = nullptr;
	int numServices = m_serviceUUIDs.size();
    int rc = 0;
    uint8_t addressType;
	
	if (numServices > 0) {
		for (int i = 0; i < numServices; i++) {
			if(m_serviceUUIDs[i].getNative()->u.type == BLE_UUID_TYPE_16){
				m_advData.num_uuids16++;
                if(nullptr == (uuids16 = (ble_uuid16_t*)realloc(uuids16, m_advData.num_uuids16 * sizeof(ble_uuid16_t)))) {
                    NIMBLE_LOGE(LOG_TAG, "Error, no mem");
                    abort();
                }
                memcpy(&uuids16[m_advData.num_uuids16].value, &m_serviceUUIDs[i].getNative()->u16.value, sizeof(uint16_t));
                uuids16[m_advData.num_uuids16].u.type = BLE_UUID_TYPE_16;
				char buf[BLE_UUID_STR_LEN];
				ble_uuid_to_str(&uuids128[m_advData.num_uuids128].u, buf);
				NIMBLE_LOGE(LOG_TAG, "Advertising UUID: %s", buf);
                m_advData.uuids16_is_complete = 1;
                m_advData.uuids16 = uuids16;  
			}
			if(m_serviceUUIDs[i].getNative()->u.type == BLE_UUID_TYPE_32){
				m_advData.num_uuids32++;
                if(nullptr == (uuids32 = (ble_uuid32_t*)realloc(uuids32, m_advData.num_uuids32 * sizeof(ble_uuid32_t)))) {
                    NIMBLE_LOGE(LOG_TAG, "Error, no mem");
                    abort();
                }
                memcpy(&uuids32[m_advData.num_uuids32].value, &m_serviceUUIDs[i].getNative()->u32.value, sizeof(uint32_t));
                uuids32[m_advData.num_uuids32].u.type = BLE_UUID_TYPE_32;
				char buf[BLE_UUID_STR_LEN];
				ble_uuid_to_str(&uuids128[m_advData.num_uuids128].u, buf);
				NIMBLE_LOGE(LOG_TAG, "Advertising UUID: %s", buf);
                m_advData.uuids32_is_complete = 1;
                m_advData.uuids32 = uuids32; 
			}
			if(m_serviceUUIDs[i].getNative()->u.type == BLE_UUID_TYPE_128){
				m_advData.num_uuids128++;
                if(nullptr == (uuids128 = (ble_uuid128_t*)realloc(uuids128, m_advData.num_uuids128 * sizeof(ble_uuid128_t)))) {
                    NIMBLE_LOGE(LOG_TAG, "Error, no mem");
                    abort();
                }
                memcpy(&uuids128[m_advData.num_uuids128].value, &m_serviceUUIDs[i].getNative()->u128.value, 16);
                uuids128[m_advData.num_uuids128].u.type = BLE_UUID_TYPE_128;
				char buf[BLE_UUID_STR_LEN];
				ble_uuid_to_str(&uuids128[m_advData.num_uuids128].u, buf);
				NIMBLE_LOGE(LOG_TAG, "Advertising UUID: %s", buf);
                m_advData.uuids128_is_complete = 1;
                m_advData.uuids128 = uuids128; 
			}
		}
        
        rc = ble_gap_adv_set_fields(&m_advData);
        if (rc != 0) {
            NIMBLE_LOGE(LOG_TAG, "error setting advertisement data; rc=%d, %s", rc, NimBLEUtils::returnCodeToString(rc));
            abort();
        }
        
        rc = ble_hs_id_infer_auto(0, &addressType);
        if (rc != 0) {
            NIMBLE_LOGE(LOG_TAG, "error determining address type; rc=%d, %s", rc, NimBLEUtils::returnCodeToString(rc));
            abort();
        }
        
		rc = ble_gatts_start();
		if (rc != 0) {
			NIMBLE_LOGE(LOG_TAG, "ble_gatts_start; rc=%d, %s", rc, NimBLEUtils::returnCodeToString(rc));
			abort();
		}
		
        rc = ble_gap_adv_start(addressType, NULL, BLE_HS_FOREVER,
                           &m_advParams, NULL, NULL);
        if (rc != 0) {
            NIMBLE_LOGE(LOG_TAG, "error enabling advertisement; rc=%d, %s", rc, NimBLEUtils::returnCodeToString(rc));
            abort();
        }
    }
/*
		m_advData.service_uuid_len = 16 * numServices;
		m_advData.p_service_uuid = new uint8_t[m_advData.service_uuid_len];
		uint8_t* p = m_advData.p_service_uuid;
		for (int i = 0; i < numServices; i++) {
			ESP_LOGD(LOG_TAG, "- advertising service: %s", m_serviceUUIDs[i].toString().c_str());
			BLEUUID serviceUUID128 = m_serviceUUIDs[i].to128();
			memcpy(p, serviceUUID128.getNative()->uuid.uuid128, 16);
			p += 16;
		}
	} else {
		m_advData.service_uuid_len = 0;
		ESP_LOGD(LOG_TAG, "- no services advertised");
	}
*/
/*
	// We have a vector of service UUIDs that we wish to advertise.  In order to use the
	// ESP-IDF framework, these must be supplied in a contiguous array of their 128bit (16 byte)
	// representations.  If we have 1 or more services to advertise then we allocate enough
	// storage to host them and then copy them in one at a time into the contiguous storage.
	int numServices = m_serviceUUIDs.size();
	if (numServices > 0) {
		m_advData.service_uuid_len = 16 * numServices;
		m_advData.p_service_uuid = new uint8_t[m_advData.service_uuid_len];
		uint8_t* p = m_advData.p_service_uuid;
		for (int i = 0; i < numServices; i++) {
			ESP_LOGD(LOG_TAG, "- advertising service: %s", m_serviceUUIDs[i].toString().c_str());
			BLEUUID serviceUUID128 = m_serviceUUIDs[i].to128();
			memcpy(p, serviceUUID128.getNative()->uuid.uuid128, 16);
			p += 16;
		}
	} else {
		m_advData.service_uuid_len = 0;
		ESP_LOGD(LOG_TAG, "- no services advertised");
	}

	esp_err_t errRc;

	if (!m_customAdvData) {
		// Set the configuration for advertising.
		m_advData.set_scan_rsp = false;
		m_advData.include_name = !m_scanResp;
		m_advData.include_txpower = !m_scanResp;
		errRc = ::esp_ble_gap_config_adv_data(&m_advData);
		if (errRc != ESP_OK) {
			ESP_LOGE(LOG_TAG, "<< esp_ble_gap_config_adv_data: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
			return;
		}
	}

	if (!m_customScanResponseData && m_scanResp) {
		m_advData.set_scan_rsp = true;
		m_advData.include_name = m_scanResp;
		m_advData.include_txpower = m_scanResp;
		errRc = ::esp_ble_gap_config_adv_data(&m_advData);
		if (errRc != ESP_OK) {
			ESP_LOGE(LOG_TAG, "<< esp_ble_gap_config_adv_data (Scan response): rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
			return;
		}
	}

	// If we had services to advertise then we previously allocated some storage for them.
	// Here we release that storage.
	if (m_advData.service_uuid_len > 0) {
		delete[] m_advData.p_service_uuid;
		m_advData.p_service_uuid = nullptr;
	}

	// Start advertising.
	errRc = ::esp_ble_gap_start_advertising(&m_advParams);
	if (errRc != ESP_OK) {
		ESP_LOGE(LOG_TAG, "<< esp_ble_gap_start_advertising: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		return;
	}
*/
	NIMBLE_LOGD(LOG_TAG, "<< Advertising start");
	ble_gatts_show_local();
} // start


/**
 * @brief Stop advertising.
 * Stop advertising.
 * @return N/A.
 */
void NimBLEAdvertising::stop() {
	NIMBLE_LOGD(LOG_TAG, ">> stop");
	/*
	esp_err_t errRc = ::esp_ble_gap_stop_advertising();
	if (errRc != ESP_OK) {
		ESP_LOGE(LOG_TAG, "esp_ble_gap_stop_advertising: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		return;
	}
	*/
	NIMBLE_LOGD(LOG_TAG, "<< stop");
} // stop

/**
 * @brief Add data to the payload to be advertised.
 * @param [in] data The data to be added to the payload.
 */
 /*
void NimBLEAdvertisementData::addData(std::string data) {
	if ((m_payload.length() + data.length()) > ESP_BLE_ADV_DATA_LEN_MAX) {
		return;
	}
	m_payload.append(data);
} // addData
*/

/**
 * @brief Set the appearance.
 * @param [in] appearance The appearance code value.
 *
 * See also:
 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.gap.appearance.xml
 */
 /*
void NimBLEAdvertisementData::setAppearance(uint16_t appearance) {
	char cdata[2];
	cdata[0] = 3;
	cdata[1] = ESP_BLE_AD_TYPE_APPEARANCE; // 0x19
	addData(std::string(cdata, 2) + std::string((char*) &appearance, 2));
} // setAppearance
*/

/**
 * @brief Set the complete services.
 * @param [in] uuid The single service to advertise.
 */
 /*
void NimBLEAdvertisementData::setCompleteServices(BLEUUID uuid) {
	char cdata[2];
	switch (uuid.bitSize()) {
		case 16: {
			// [Len] [0x02] [LL] [HH]
			cdata[0] = 3;
			cdata[1] = ESP_BLE_AD_TYPE_16SRV_CMPL;  // 0x03
			addData(std::string(cdata, 2) + std::string((char*) &uuid.getNative()->uuid.uuid16, 2));
			break;
		}

		case 32: {
			// [Len] [0x04] [LL] [LL] [HH] [HH]
			cdata[0] = 5;
			cdata[1] = ESP_BLE_AD_TYPE_32SRV_CMPL;  // 0x05
			addData(std::string(cdata, 2) + std::string((char*) &uuid.getNative()->uuid.uuid32, 4));
			break;
		}

		case 128: {
			// [Len] [0x04] [0] [1] ... [15]
			cdata[0] = 17;
			cdata[1] = ESP_BLE_AD_TYPE_128SRV_CMPL;  // 0x07
			addData(std::string(cdata, 2) + std::string((char*) uuid.getNative()->uuid.uuid128, 16));
			break;
		}

		default:
			return;
	}
} // setCompleteServices
*/

/**
 * @brief Set the advertisement flags.
 * @param [in] The flags to be set in the advertisement.
 *
 * * ESP_BLE_ADV_FLAG_LIMIT_DISC
 * * ESP_BLE_ADV_FLAG_GEN_DISC
 * * ESP_BLE_ADV_FLAG_BREDR_NOT_SPT
 * * ESP_BLE_ADV_FLAG_DMT_CONTROLLER_SPT
 * * ESP_BLE_ADV_FLAG_DMT_HOST_SPT
 * * ESP_BLE_ADV_FLAG_NON_LIMIT_DISC
 */
 /*
void NimBLEAdvertisementData::setFlags(uint8_t flag) {
	char cdata[3];
	cdata[0] = 2;
	cdata[1] = ESP_BLE_AD_TYPE_FLAG;  // 0x01
	cdata[2] = flag;
	addData(std::string(cdata, 3));
} // setFlag
*/


/**
 * @brief Set manufacturer specific data.
 * @param [in] data Manufacturer data.
 */
 /*
void NimBLEAdvertisementData::setManufacturerData(std::string data) {
	ESP_LOGD("BLEAdvertisementData", ">> setManufacturerData");
	char cdata[2];
	cdata[0] = data.length() + 1;
	cdata[1] = ESP_BLE_AD_MANUFACTURER_SPECIFIC_TYPE;  // 0xff
	addData(std::string(cdata, 2) + data);
	ESP_LOGD("BLEAdvertisementData", "<< setManufacturerData");
} // setManufacturerData
*/

/**
 * @brief Set the name.
 * @param [in] The complete name of the device.
 */
 /*
void NimBLEAdvertisementData::setName(std::string name) {
	ESP_LOGD("NimBLEAdvertisementData", ">> setName: %s", name.c_str());
	char cdata[2];
	cdata[0] = name.length() + 1;
	cdata[1] = ESP_BLE_AD_TYPE_NAME_CMPL;  // 0x09
	addData(std::string(cdata, 2) + name);
	ESP_LOGD("NimBLEAdvertisementData", "<< setName");
} // setName
*/

/**
 * @brief Set the partial services.
 * @param [in] uuid The single service to advertise.
 */
 /*
void NimBLEAdvertisementData::setPartialServices(NimBLEUUID uuid) {
	char cdata[2];
	switch (uuid.bitSize()) {
		case 16: {
			// [Len] [0x02] [LL] [HH]
			cdata[0] = 3;
			cdata[1] = ESP_BLE_AD_TYPE_16SRV_PART;  // 0x02
			addData(std::string(cdata, 2) + std::string((char *) &uuid.getNative()->uuid.uuid16, 2));
			break;
		}

		case 32: {
			// [Len] [0x04] [LL] [LL] [HH] [HH]
			cdata[0] = 5;
			cdata[1] = ESP_BLE_AD_TYPE_32SRV_PART; // 0x04
			addData(std::string(cdata, 2) + std::string((char *) &uuid.getNative()->uuid.uuid32, 4));
			break;
		}

		case 128: {
			// [Len] [0x04] [0] [1] ... [15]
			cdata[0] = 17;
			cdata[1] = ESP_BLE_AD_TYPE_128SRV_PART;  // 0x06
			addData(std::string(cdata, 2) + std::string((char *) &uuid.getNative()->uuid.uuid128, 16));
			break;
		}

		default:
			return;
	}
} // setPartialServices
*/

/**
 * @brief Set the service data (UUID + data)
 * @param [in] uuid The UUID to set with the service data.  Size of UUID will be used.
 * @param [in] data The data to be associated with the service data advert.
 */
 /*
void NimBLEAdvertisementData::setServiceData(BLEUUID uuid, std::string data) {
	char cdata[2];
	switch (uuid.bitSize()) {
		case 16: {
			// [Len] [0x16] [UUID16] data
			cdata[0] = data.length() + 3;
			cdata[1] = ESP_BLE_AD_TYPE_SERVICE_DATA;  // 0x16
			addData(std::string(cdata, 2) + std::string((char*) &uuid.getNative()->uuid.uuid16, 2) + data);
			break;
		}

		case 32: {
			// [Len] [0x20] [UUID32] data
			cdata[0] = data.length() + 5;
			cdata[1] = ESP_BLE_AD_TYPE_32SERVICE_DATA; // 0x20
			addData(std::string(cdata, 2) + std::string((char*) &uuid.getNative()->uuid.uuid32, 4) + data);
			break;
		}

		case 128: {
			// [Len] [0x21] [UUID128] data
			cdata[0] = data.length() + 17;
			cdata[1] = ESP_BLE_AD_TYPE_128SERVICE_DATA;  // 0x21
			addData(std::string(cdata, 2) + std::string((char*) &uuid.getNative()->uuid.uuid128, 16) + data);
			break;
		}

		default:
			return;
	}
} // setServiceData
*/

/**
 * @brief Set the short name.
 * @param [in] The short name of the device.
 */
 /*
void NimBLEAdvertisementData::setShortName(std::string name) {
	ESP_LOGD("NimBLEAdvertisementData", ">> setShortName: %s", name.c_str());
	char cdata[2];
	cdata[0] = name.length() + 1;
	cdata[1] = ESP_BLE_AD_TYPE_NAME_SHORT;  // 0x08
	addData(std::string(cdata, 2) + name);
	ESP_LOGD("NimBLEAdvertisementData", "<< setShortName");
} // setShortName
*/

/**
 * @brief Retrieve the payload that is to be advertised.
 * @return The payload that is to be advertised.
 */
std::string NimBLEAdvertisementData::getPayload() {
	return m_payload;
} // getPayload
/*
void NimBLEAdvertising::handleGAPEvent(
		esp_gap_ble_cb_event_t  event,
		esp_ble_gap_cb_param_t* param)  {

	ESP_LOGD(LOG_TAG, "handleGAPEvent [event no: %d]", (int)event);

	switch(event) {
		case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT: {
			// m_semaphoreSetAdv.give();
			break;
		}
		case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT: {
			// m_semaphoreSetAdv.give();
			break;
		}
		case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: {
			// m_semaphoreSetAdv.give();
			break;
		}
		case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT: {
			ESP_LOGI(LOG_TAG, "STOP advertising");
			start();
			break;
		}
		default:
			break;
	}
}
*/

#endif /* CONFIG_BT_ENABLED */