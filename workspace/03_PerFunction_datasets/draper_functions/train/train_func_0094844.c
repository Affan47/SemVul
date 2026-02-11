iwl_dbgfs_d0i3_refs_write(struct iwl_mvm *mvm, char *buf,
					 size_t count, loff_t *ppos)
{
	unsigned long value;
	int ret;
	bool taken;

	ret = kstrtoul(buf, 10, &value);
	if (ret < 0)
		return ret;

	mutex_lock(&mvm->mutex);

	taken = mvm->refs[IWL_MVM_REF_USER];
	if (value == 1 && !taken)
		iwl_mvm_ref(mvm, IWL_MVM_REF_USER);
	else if (value == 0 && taken)
		iwl_mvm_unref(mvm, IWL_MVM_REF_USER);
	else
		ret = -EINVAL;

	mutex_unlock(&mvm->mutex);

	if (ret < 0)
		return ret;
	return count;
}
