iwl_dbgfs_fw_nmi_write(struct iwl_mvm *mvm, char *buf,
				      size_t count, loff_t *ppos)
{
	int ret = iwl_mvm_ref_sync(mvm, IWL_MVM_REF_NMI);
	if (ret)
		return ret;

	iwl_force_nmi(mvm->trans);

	iwl_mvm_unref(mvm, IWL_MVM_REF_NMI);

	return count;
}
