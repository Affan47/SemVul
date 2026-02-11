wilc_wlan_cfg_set_wid(u8 *frame, u32 offset, u16 id, u8 *buf, int size)
{
	u8 type = (id >> 12) & 0xf;
	int ret = 0;

	if (type == 0) {
		if (size >= 1)
			ret = wilc_wlan_cfg_set_byte(frame, offset, id, *buf);
	} else if (type == 1) {
		if (size >= 2)
			ret = wilc_wlan_cfg_set_hword(frame, offset, id, *((u16 *)buf));
	} else if (type == 2) {
		if (size >= 4)
			ret = wilc_wlan_cfg_set_word(frame, offset, id, *((u32 *)buf));
	} else if (type == 3) {
		ret = wilc_wlan_cfg_set_str(frame, offset, id, buf, size);
	} else if (type == 4) {
		ret = wilc_wlan_cfg_set_bin(frame, offset, id, buf, size);
	} else {
		g_mac.dPrint(N_ERR, "illegal id\n");
	}

	return ret;
}
