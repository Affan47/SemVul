ath10k_spectral_scan_trigger(struct ath10k *ar)
{
	struct ath10k_vif *arvif;
	int res;
	int vdev_id;

	lockdep_assert_held(&ar->conf_mutex);

	arvif = ath10k_get_spectral_vdev(ar);
	if (!arvif)
		return -ENODEV;
	vdev_id = arvif->vdev_id;

	if (ar->spectral.mode == SPECTRAL_DISABLED)
		return 0;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	if (res < 0)
		return res;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_TRIGGER,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	if (res < 0)
		return res;

	return 0;
}
