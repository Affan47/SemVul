il_send_remove_station(struct il_priv *il, const u8 * addr, int sta_id,
		       bool temporary)
{
	struct il_rx_pkt *pkt;
	int ret;

	unsigned long flags_spin;
	struct il_rem_sta_cmd rm_sta_cmd;

	struct il_host_cmd cmd = {
		.id = C_REM_STA,
		.len = sizeof(struct il_rem_sta_cmd),
		.flags = CMD_SYNC,
		.data = &rm_sta_cmd,
	};

	memset(&rm_sta_cmd, 0, sizeof(rm_sta_cmd));
	rm_sta_cmd.num_sta = 1;
	memcpy(&rm_sta_cmd.addr, addr, ETH_ALEN);

	cmd.flags |= CMD_WANT_SKB;

	ret = il_send_cmd(il, &cmd);

	if (ret)
		return ret;

	pkt = (struct il_rx_pkt *)cmd.reply_page;
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from C_REM_STA (0x%08X)\n", pkt->hdr.flags);
		ret = -EIO;
	}

	if (!ret) {
		switch (pkt->u.rem_sta.status) {
		case REM_STA_SUCCESS_MSK:
			if (!temporary) {
				spin_lock_irqsave(&il->sta_lock, flags_spin);
				il_sta_ucode_deactivate(il, sta_id);
				spin_unlock_irqrestore(&il->sta_lock,
						       flags_spin);
			}
			D_ASSOC("C_REM_STA PASSED\n");
			break;
		default:
			ret = -EIO;
			IL_ERR("C_REM_STA failed\n");
			break;
		}
	}
	il_free_pages(il, cmd.reply_page);

	return ret;
}
