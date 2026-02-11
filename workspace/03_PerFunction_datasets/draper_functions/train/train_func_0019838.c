wilc_wlan_cfg_set(int start, u32 wid, u8 *buffer, u32 buffer_size,
		      int commit, u32 drvHandler)
{
	wilc_wlan_dev_t *p = &g_wlan;
	u32 offset;
	int ret_size;


	if (p->cfg_frame_in_use)
		return 0;

	if (start)
		p->cfg_frame_offset = 0;

	offset = p->cfg_frame_offset;
	ret_size = wilc_wlan_cfg_set_wid(p->cfg_frame.frame, offset, (u16)wid,
					 buffer, buffer_size);
	offset += ret_size;
	p->cfg_frame_offset = offset;

	if (commit) {
		PRINT_D(TX_DBG, "[WILC]PACKET Commit with sequence number %d\n", p->cfg_seq_no);
		PRINT_D(RX_DBG, "Processing cfg_set()\n");
		p->cfg_frame_in_use = 1;

		if (wilc_wlan_cfg_commit(WILC_CFG_SET, drvHandler))
			ret_size = 0;

		if (linux_wlan_lock_timeout(&g_linux_wlan->cfg_event,
					    CFG_PKTS_TIMEOUT)) {
			PRINT_D(TX_DBG, "Set Timed Out\n");
			ret_size = 0;
		}
		p->cfg_frame_in_use = 0;
		p->cfg_frame_offset = 0;
		p->cfg_seq_no += 1;

	}

	return ret_size;
}
