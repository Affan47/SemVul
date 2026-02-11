ufshcd_probe_hba(struct ufs_hba *hba)
{
	int ret;

	ret = ufshcd_link_startup(hba);
	if (ret)
		goto out;

	ufshcd_init_pwr_info(hba);


	ufshcd_set_link_active(hba);

	ret = ufshcd_verify_dev_init(hba);
	if (ret)
		goto out;

	ret = ufshcd_complete_dev_init(hba);
	if (ret)
		goto out;


	ufshcd_set_ufs_dev_active(hba);
	ufshcd_force_reset_auto_bkops(hba);
	hba->ufshcd_state = UFSHCD_STATE_OPERATIONAL;
	hba->wlun_dev_clr_ua = true;

	if (ufshcd_get_max_pwr_mode(hba)) {
		dev_err(hba->dev,
			"%s: Failed getting max supported power mode\n",
			__func__);
	} else {
		ret = ufshcd_config_pwr_mode(hba, &hba->max_pwr_info.info);
		if (ret)
			dev_err(hba->dev, "%s: Failed setting power mode, err = %d\n",
					__func__, ret);
	}


	if (!ufshcd_eh_in_progress(hba) && !hba->pm_op_in_progress) {
		bool flag;


		memset(&hba->dev_info, 0, sizeof(hba->dev_info));
		if (!ufshcd_query_flag(hba, UPIU_QUERY_OPCODE_READ_FLAG,
				       QUERY_FLAG_IDN_PWR_ON_WPE, &flag))
			hba->dev_info.f_power_on_wp_en = flag;

		if (!hba->is_init_prefetch)
			ufshcd_init_icc_levels(hba);


		if (ufshcd_scsi_add_wlus(hba))
			goto out;

		scsi_scan_host(hba->host);
		pm_runtime_put_sync(hba->dev);
	}

	if (!hba->is_init_prefetch)
		hba->is_init_prefetch = true;


	if (ufshcd_is_clkscaling_enabled(hba))
		devfreq_resume_device(hba->devfreq);

out:


	if (ret && !ufshcd_eh_in_progress(hba) && !hba->pm_op_in_progress) {
		pm_runtime_put_sync(hba->dev);
		ufshcd_hba_exit(hba);
	}

	return ret;
}
