iwl_dbgfs_tof_range_abort_write(struct ieee80211_vif *vif,
					       char *buf,
					       size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int abort_id, ret = 0;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("abort_id=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.last_abort_id = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("send_range_abort=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value) {
			abort_id = mvm->tof_data.last_abort_id;
			ret = iwl_mvm_tof_range_abort_cmd(mvm, abort_id);
			goto out;
		}
	}

out:
	mutex_unlock(&mvm->mutex);
	return ret ?: count;
}
