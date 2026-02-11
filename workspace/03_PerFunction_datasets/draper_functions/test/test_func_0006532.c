rtw_validate_frame_ies(const u8 *start, uint len)
{
	const u8 *pos = start;
	int left = len;
	int unknown = 0;

	while (left >= 2) {
		u8 id, elen;

		id = *pos++;
		elen = *pos++;
		left -= 2;

		if (elen > left) {
			DBG_8723A("%s: IEEE 802.11 failed (id =%d elen =%d "
				  "left =%i)\n", __func__, id, elen, left);
			return -EINVAL;
		}

		switch (id) {
		case WLAN_EID_SSID:
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_FH_PARAMS:
		case WLAN_EID_DS_PARAMS:
		case WLAN_EID_CF_PARAMS:
		case WLAN_EID_TIM:
		case WLAN_EID_IBSS_PARAMS:
		case WLAN_EID_CHALLENGE:
		case WLAN_EID_ERP_INFO:
		case WLAN_EID_EXT_SUPP_RATES:
			break;
		case WLAN_EID_VENDOR_SPECIFIC:
			if (rtw_validate_vendor_specific_ies(pos, elen))
				unknown++;
			break;
		case WLAN_EID_RSN:
		case WLAN_EID_PWR_CAPABILITY:
		case WLAN_EID_SUPPORTED_CHANNELS:
		case WLAN_EID_MOBILITY_DOMAIN:
		case WLAN_EID_FAST_BSS_TRANSITION:
		case WLAN_EID_TIMEOUT_INTERVAL:
		case WLAN_EID_HT_CAPABILITY:
		case WLAN_EID_HT_OPERATION:
		default:
			unknown++;
			DBG_8723A("%s IEEE 802.11 ignored unknown element "
				  "(id =%d elen =%d)\n", __func__, id, elen);
			break;
		}

		left -= elen;
		pos += elen;
	}

	if (left)
		return -EINVAL;

	return 0;
}
