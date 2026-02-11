iwl_dbgfs_tof_range_response_read(struct file *file,
						 char __user *user_buf,
						 size_t count, loff_t *ppos)
{
	struct ieee80211_vif *vif = file->private_data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	char *buf;
	int pos = 0;
	const size_t bufsz = sizeof(struct iwl_tof_range_rsp_ntfy) + 256;
	struct iwl_tof_range_rsp_ntfy *cmd;
	int i, ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	mutex_lock(&mvm->mutex);
	cmd = &mvm->tof_data.range_resp;

	pos += scnprintf(buf + pos, bufsz - pos, "request_id = %d\n",
			 cmd->request_id);
	pos += scnprintf(buf + pos, bufsz - pos, "status = %d\n",
			 cmd->request_status);
	pos += scnprintf(buf + pos, bufsz - pos, "last_in_batch = %d\n",
			 cmd->last_in_batch);
	pos += scnprintf(buf + pos, bufsz - pos, "num_of_aps = %d\n",
			 cmd->num_of_aps);
	for (i = 0; i < cmd->num_of_aps; i++) {
		struct iwl_tof_range_rsp_ap_entry_ntfy *ap = &cmd->ap[i];

		pos += scnprintf(buf + pos, bufsz - pos,
				"ap %.2d: bssid=%pM status=%hhd bw=%hhd"
				" rtt=%d rtt_var=%d rtt_spread=%d"
				" rssi=%hhd  rssi_spread=%hhd"
				" range=%d range_var=%d"
				" time_stamp=%d\n",
				i, ap->bssid, ap->measure_status,
				ap->measure_bw,
				ap->rtt, ap->rtt_variance, ap->rtt_spread,
				ap->rssi, ap->rssi_spread, ap->range,
				ap->range_variance, ap->timestamp);
	}
	mutex_unlock(&mvm->mutex);

	ret = simple_read_from_buffer(user_buf, count, ppos, buf, pos);
	kfree(buf);
	return ret;
}
