iwl_mvm_dump_umac_error_log(struct iwl_mvm *mvm)
{
	struct iwl_trans *trans = mvm->trans;
	struct iwl_umac_error_event_table table;
	u32 base;

	base = mvm->umac_error_event_table;

	if (base < 0x800000) {
		IWL_ERR(mvm,
			"Not valid error log pointer 0x%08X for %s uCode\n",
			base,
			(mvm->cur_ucode == IWL_UCODE_INIT)
					? "Init" : "RT");
		return;
	}

	iwl_trans_read_mem_bytes(trans, base, &table, sizeof(table));

	if (ERROR_START_OFFSET <= table.valid * ERROR_ELEM_SIZE) {
		IWL_ERR(trans, "Start IWL Error Log Dump:\n");
		IWL_ERR(trans, "Status: 0x%08lX, count: %d\n",
			mvm->status, table.valid);
	}

	IWL_ERR(mvm, "0x%08X | %s\n", table.error_id,
		desc_lookup(table.error_id));
	IWL_ERR(mvm, "0x%08X | umac branchlink1\n", table.blink1);
	IWL_ERR(mvm, "0x%08X | umac branchlink2\n", table.blink2);
	IWL_ERR(mvm, "0x%08X | umac interruptlink1\n", table.ilink1);
	IWL_ERR(mvm, "0x%08X | umac interruptlink2\n", table.ilink2);
	IWL_ERR(mvm, "0x%08X | umac data1\n", table.data1);
	IWL_ERR(mvm, "0x%08X | umac data2\n", table.data2);
	IWL_ERR(mvm, "0x%08X | umac data3\n", table.data3);
	IWL_ERR(mvm, "0x%08X | umac major\n", table.umac_major);
	IWL_ERR(mvm, "0x%08X | umac minor\n", table.umac_minor);
	IWL_ERR(mvm, "0x%08X | frame pointer\n", table.frame_pointer);
	IWL_ERR(mvm, "0x%08X | stack pointer\n", table.stack_pointer);
	IWL_ERR(mvm, "0x%08X | last host cmd\n", table.cmd_header);
	IWL_ERR(mvm, "0x%08X | isr status reg\n", table.nic_isr_pref);
}
