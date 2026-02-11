rtw_get_wps_ie(u8 *in_ie, uint in_len, u8 *wps_ie, uint *wps_ielen)
{
	uint cnt;
	u8 *wpsie_ptr = NULL;
	u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

	if (wps_ielen)
		*wps_ielen = 0;

	if (!in_ie || in_len <= 0)
		return wpsie_ptr;

	cnt = 0;

	while (cnt < in_len) {
		eid = in_ie[cnt];

		if ((eid == _WPA_IE_ID_) && (!memcmp(&in_ie[cnt+2], wps_oui, 4))) {
			wpsie_ptr = &in_ie[cnt];

			if (wps_ie)
				memcpy(wps_ie, &in_ie[cnt], in_ie[cnt+1]+2);

			if (wps_ielen)
				*wps_ielen = in_ie[cnt+1]+2;

			cnt += in_ie[cnt+1]+2;

			break;
		} else {
			cnt += in_ie[cnt+1]+2;
		}
	}
	return wpsie_ptr;
}
