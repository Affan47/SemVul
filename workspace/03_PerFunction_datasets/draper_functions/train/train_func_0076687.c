iwl_dbgfs_tof_range_request_read(struct file *file,
						char __user *user_buf,
						size_t count, loff_t *ppos)
{
	struct ieee80211_vif *vif = file->private_data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	char buf[512];
	int pos = 0;
	const size_t bufsz = sizeof(buf);
	struct iwl_tof_range_req_cmd *cmd;
	int i;

	cmd = &mvm->tof_data.range_req;

	mutex_lock(&mvm->mutex);

	pos += scnprintf(buf + pos, bufsz - pos, "request_id= %d\n",
			 cmd->request_id);
	pos += scnprintf(buf + pos, bufsz - pos, "initiator= %d\n",
			 cmd->initiator);
	pos += scnprintf(buf + pos, bufsz - pos, "one_sided_los_disable = %d\n",
			 cmd->one_sided_los_disable);
	pos += scnprintf(buf + pos, bufsz - pos, "req_timeout= %d\n",
			 cmd->req_timeout);
	pos += scnprintf(buf + pos, bufsz - pos, "report_policy= %d\n",
			 cmd->report_policy);
	pos += scnprintf(buf + pos, bufsz - pos, "macaddr_random= %d\n",
			 cmd->macaddr_random);
	pos += scnprintf(buf + pos, bufsz - pos, "macaddr_template= %pM\n",
			 cmd->macaddr_template);
	pos += scnprintf(buf + pos, bufsz - pos, "macaddr_mask= %pM\n",
			 cmd->macaddr_mask);
	pos += scnprintf(buf + pos, bufsz - pos, "num_of_ap= %d\n",
			 cmd->num_of_ap);
	for (i = 0; i < cmd->num_of_ap; i++) {
		struct iwl_tof_range_req_ap_entry *ap = &cmd->ap[i];

		pos += scnprintf(buf + pos, bufsz - pos,
				"ap %.2d: channel_num=%hhd bw=%hhd"
				" control=%hhd bssid=%pM type=%hhd"
				" num_of_bursts=%hhd burst_period=%hd ftm=%hhd"
				" retries=%hhd tsf_delta=%d"
				" tsf_delta_direction=%hhd location_req=0x%hhx "
				" asap=%hhd enable=%hhd rssi=%hhd\n",
				i, ap->channel_num, ap->bandwidth,
				ap->ctrl_ch_position, ap->bssid,
				ap->measure_type, ap->num_of_bursts,
				ap->burst_period, ap->samples_per_burst,
				ap->retries_per_sample, ap->tsf_delta,
				ap->tsf_delta_direction,
				ap->location_req, ap->asap_mode,
				ap->enable_dyn_ack, ap->rssi);
	}

	mutex_unlock(&mvm->mutex);

	return simple_read_from_buffer(user_buf, count, ppos, buf, pos);
}
