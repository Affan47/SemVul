ath10k_core_unregister(struct ath10k *ar)
{
	cancel_work_sync(&ar->register_work);

	if (!test_bit(ATH10K_FLAG_CORE_REGISTERED, &ar->dev_flags))
		return;

	ath10k_thermal_unregister(ar);


	ath10k_spectral_destroy(ar);


	ath10k_mac_unregister(ar);

	ath10k_testmode_destroy(ar);

	ath10k_core_free_firmware_files(ar);
	ath10k_core_free_board_files(ar);

	ath10k_debug_unregister(ar);
}
