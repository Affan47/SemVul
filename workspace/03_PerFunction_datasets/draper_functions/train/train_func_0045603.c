ath10k_scan_stop(struct ath10k *ar)
{
	struct wmi_stop_scan_arg arg = {
		.req_id = 1,
		.req_type = WMI_SCAN_STOP_ONE,
		.u.scan_id = ATH10K_SCAN_ID,
	};
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_stop_scan(ar, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to stop wmi scan: %d\n", ret);
		goto out;
	}

	ret = wait_for_completion_timeout(&ar->scan.completed, 3*HZ);
	if (ret == 0) {
		ath10k_warn(ar, "failed to receive scan abortion completion: timed out\n");
		ret = -ETIMEDOUT;
	} else if (ret > 0) {
		ret = 0;
	}

out:


	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state != ATH10K_SCAN_IDLE)
		__ath10k_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	return ret;
}
