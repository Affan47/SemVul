iwl_mvm_fw_error_dump_wk(struct work_struct *work)
{
	struct iwl_mvm *mvm =
		container_of(work, struct iwl_mvm, fw_dump_wk.work);

	if (iwl_mvm_ref_sync(mvm, IWL_MVM_REF_FW_DBG_COLLECT))
		return;

	mutex_lock(&mvm->mutex);


	if (mvm->cfg->device_family == IWL_DEVICE_FAMILY_7000) {
		iwl_set_bits_prph(mvm->trans, MON_BUFF_SAMPLE_CTL, 0x100);
	} else {
		iwl_write_prph(mvm->trans, DBGC_IN_SAMPLE, 0);

		udelay(100);
	}

	iwl_mvm_fw_error_dump(mvm);


	WARN_ON_ONCE((!test_bit(STATUS_FW_ERROR, &mvm->trans->status)) &&
		     mvm->fw->dbg_dest_tlv &&
		     iwl_mvm_start_fw_dbg_conf(mvm, mvm->fw_dbg_conf));

	mutex_unlock(&mvm->mutex);

	iwl_mvm_unref(mvm, IWL_MVM_REF_FW_DBG_COLLECT);
}
