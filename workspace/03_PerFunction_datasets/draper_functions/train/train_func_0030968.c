ath10k_wow_init(struct ath10k *ar)
{
	if (!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT, ar->fw_features))
		return 0;

	if (WARN_ON(!test_bit(WMI_SERVICE_WOW, ar->wmi.svc_map)))
		return -EINVAL;

	ar->wow.wowlan_support = ath10k_wowlan_support;
	ar->wow.wowlan_support.n_patterns = ar->wow.max_num_patterns;
	ar->hw->wiphy->wowlan = &ar->wow.wowlan_support;

	return 0;
}
