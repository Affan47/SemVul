ath10k_wmi_event_vdev_start_resp(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_vdev_start_ev_arg arg = {};
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_START_RESP_EVENTID\n");

	ret = ath10k_wmi_pull_vdev_start(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse vdev start event: %d\n", ret);
		return;
	}

	if (WARN_ON(__le32_to_cpu(arg.status)))
		return;

	complete(&ar->vdev_setup_done);
}
