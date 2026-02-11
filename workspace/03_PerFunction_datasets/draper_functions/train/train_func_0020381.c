iwl_mvm_rx_ant_coupling_notif(struct iwl_mvm *mvm,
				   struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	u32 ant_isolation = le32_to_cpup((void *)pkt->data);
	struct iwl_bt_coex_corun_lut_update_cmd cmd = {};
	u8 __maybe_unused lower_bound, upper_bound;
	u8 lut;

	if (!fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_BT_COEX_SPLIT)) {
		iwl_mvm_rx_ant_coupling_notif_old(mvm, rxb);
		return;
	}

	if (!iwl_mvm_bt_is_plcr_supported(mvm))
		return;

	lockdep_assert_held(&mvm->mutex);


	if (unlikely(mvm->bt_force_ant_mode != BT_FORCE_ANT_DIS))
		return;

	if (ant_isolation ==  mvm->last_ant_isol)
		return;

	for (lut = 0; lut < ARRAY_SIZE(antenna_coupling_ranges) - 1; lut++)
		if (ant_isolation < antenna_coupling_ranges[lut + 1].range)
			break;

	lower_bound = antenna_coupling_ranges[lut].range;

	if (lut < ARRAY_SIZE(antenna_coupling_ranges) - 1)
		upper_bound = antenna_coupling_ranges[lut + 1].range;
	else
		upper_bound = antenna_coupling_ranges[lut].range;

	IWL_DEBUG_COEX(mvm, "Antenna isolation=%d in range [%d,%d[, lut=%d\n",
		       ant_isolation, lower_bound, upper_bound, lut);

	mvm->last_ant_isol = ant_isolation;

	if (mvm->last_corun_lut == lut)
		return;

	mvm->last_corun_lut = lut;


	memcpy(&cmd.corun_lut20, antenna_coupling_ranges[lut].lut20,
	       sizeof(cmd.corun_lut20));

	memcpy(&cmd.corun_lut40, antenna_coupling_ranges[lut].lut20,
	       sizeof(cmd.corun_lut40));

	if (iwl_mvm_send_cmd_pdu(mvm, BT_COEX_UPDATE_CORUN_LUT, 0,
				 sizeof(cmd), &cmd))
		IWL_ERR(mvm,
			"failed to send BT_COEX_UPDATE_CORUN_LUT command\n");
}
