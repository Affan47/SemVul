iwl_trans_pci_dump_marbh_monitor(struct iwl_trans *trans,
				 struct iwl_fw_error_dump_fw_mon *fw_mon_data,
				 u32 monitor_len)
{
	u32 buf_size_in_dwords = (monitor_len >> 2);
	u32 *buffer = (u32 *)fw_mon_data->data;
	unsigned long flags;
	u32 i;

	if (!iwl_trans_grab_nic_access(trans, false, &flags))
		return 0;

	__iwl_write_prph(trans, MON_DMARB_RD_CTL_ADDR, 0x1);
	for (i = 0; i < buf_size_in_dwords; i++)
		buffer[i] = __iwl_read_prph(trans, MON_DMARB_RD_DATA_ADDR);
	__iwl_write_prph(trans, MON_DMARB_RD_CTL_ADDR, 0x0);

	iwl_trans_release_nic_access(trans, &flags);

	return monitor_len;
}
