ath10k_wmi_event_scan_start_failed(struct ath10k *ar)
{
	lockdep_assert_held(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH10K_SCAN_IDLE:
	case ATH10K_SCAN_RUNNING:
	case ATH10K_SCAN_ABORTING:
		ath10k_warn(ar, "received scan start failed event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		break;
	case ATH10K_SCAN_STARTING:
		complete(&ar->scan.started);
		__ath10k_scan_finish(ar);
		break;
	}
}
