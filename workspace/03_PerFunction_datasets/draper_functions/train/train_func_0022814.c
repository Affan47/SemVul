ath10k_monitor_stop(struct ath10k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_monitor_vdev_stop(ar);
	if (ret) {
		ath10k_warn(ar, "failed to stop monitor vdev: %d\n", ret);
		return ret;
	}

	ret = ath10k_monitor_vdev_delete(ar);
	if (ret) {
		ath10k_warn(ar, "failed to delete monitor vdev: %d\n", ret);
		return ret;
	}

	ar->monitor_started = false;
	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor stopped\n");

	return 0;
}
