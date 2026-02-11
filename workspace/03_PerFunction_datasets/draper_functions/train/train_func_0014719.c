ath6kl_upload_testscript(struct ath6kl *ar)
{
	u32 address;
	int ret;

	if (ar->testmode != 2)
		return 0;

	if (ar->fw_testscript == NULL)
		return 0;

	address = ar->hw.testscript_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing testscript to 0x%x (%zd B)\n",
		   address, ar->fw_testscript_len);

	ret = ath6kl_bmi_write(ar, address, ar->fw_testscript,
		ar->fw_testscript_len);
	if (ret) {
		ath6kl_err("Failed to write testscript file: %d\n", ret);
		return ret;
	}

	ath6kl_bmi_write_hi32(ar, hi_ota_testscript, address);

	if ((ar->version.target_ver != AR6004_HW_1_3_VERSION) &&
	    (ar->version.target_ver != AR6004_HW_3_0_VERSION))
		ath6kl_bmi_write_hi32(ar, hi_end_ram_reserve_sz, 4096);

	ath6kl_bmi_write_hi32(ar, hi_test_apps_related, 1);

	return 0;
}
