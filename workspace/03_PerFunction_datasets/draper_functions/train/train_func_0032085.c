check_assoc_AP23a(u8 *pframe, uint len)
{
	int i;
	u8 epigram_vendor_flag;
	u8 ralink_vendor_flag;
	const u8 *p;

	epigram_vendor_flag = 0;
	ralink_vendor_flag = 0;

	for (i = 0; i < len;) {
		p = pframe + i;

		switch (p[0]) {
		case WLAN_EID_VENDOR_SPECIFIC:
			if (!memcmp(p + 2, ARTHEROS_OUI1, 3) ||
			    !memcmp(p + 2, ARTHEROS_OUI2, 3)) {
				DBG_8723A("link to Artheros AP\n");
				return HT_IOT_PEER_ATHEROS;
			} else if (!memcmp(p + 2, BROADCOM_OUI1, 3) ||
				   !memcmp(p + 2, BROADCOM_OUI2, 3)) {
				DBG_8723A("link to Broadcom AP\n");
				return HT_IOT_PEER_BROADCOM;
			} else if (!memcmp(p + 2, MARVELL_OUI, 3)) {
				DBG_8723A("link to Marvell AP\n");
				return HT_IOT_PEER_MARVELL;
			} else if (!memcmp(p + 2, RALINK_OUI, 3)) {
				if (!ralink_vendor_flag)
					ralink_vendor_flag = 1;
				else {
					DBG_8723A("link to Ralink AP\n");
					return HT_IOT_PEER_RALINK;
				}
			} else if (!memcmp(p + 2, CISCO_OUI, 3)) {
				DBG_8723A("link to Cisco AP\n");
				return HT_IOT_PEER_CISCO;
			} else if (!memcmp(p + 2, REALTEK_OUI, 3)) {
				DBG_8723A("link to Realtek 96B\n");
				return HT_IOT_PEER_REALTEK;
			} else if (!memcmp(p + 2, AIRGOCAP_OUI, 3)) {
				DBG_8723A("link to Airgo Cap\n");
				return HT_IOT_PEER_AIRGO;
			} else if (!memcmp(p + 2, EPIGRAM_OUI, 3)) {
				epigram_vendor_flag = 1;
				if (ralink_vendor_flag) {
					DBG_8723A("link to Tenda W311R AP\n");
					return HT_IOT_PEER_TENDA;
				} else
					DBG_8723A("Capture EPIGRAM_OUI\n");
			} else
				break;
		default:
			break;
		}

		i += (p[1] + 2);
	}

	if (ralink_vendor_flag && !epigram_vendor_flag) {
		DBG_8723A("link to Ralink AP\n");
		return HT_IOT_PEER_RALINK;
	} else if (ralink_vendor_flag && epigram_vendor_flag) {
		DBG_8723A("link to Tenda W311R AP\n");
		return HT_IOT_PEER_TENDA;
	} else {
		DBG_8723A("link to new AP\n");
		return HT_IOT_PEER_UNKNOWN;
	}
}
