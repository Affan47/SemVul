ufshcd_resume(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	int ret;
	enum uic_link_state old_link_state;

	hba->pm_op_in_progress = 1;
	old_link_state = hba->uic_link_state;

	ufshcd_hba_vreg_set_hpm(hba);

	ret = ufshcd_setup_clocks(hba, true);
	if (ret)
		goto out;


	ret = ufshcd_enable_irq(hba);
	if (ret)
		goto disable_irq_and_vops_clks;

	ret = ufshcd_vreg_set_hpm(hba);
	if (ret)
		goto disable_irq_and_vops_clks;


	ret = ufshcd_vops_resume(hba, pm_op);
	if (ret)
		goto disable_vreg;

	if (ufshcd_is_link_hibern8(hba)) {
		ret = ufshcd_uic_hibern8_exit(hba);
		if (!ret)
			ufshcd_set_link_active(hba);
		else
			goto vendor_suspend;
	} else if (ufshcd_is_link_off(hba)) {
		ret = ufshcd_host_reset_and_restore(hba);


		if (ret || !ufshcd_is_link_active(hba))
			goto vendor_suspend;
	}

	if (!ufshcd_is_ufs_dev_active(hba)) {
		ret = ufshcd_set_dev_pwr_mode(hba, UFS_ACTIVE_PWR_MODE);
		if (ret)
			goto set_old_link_state;
	}

	if (ufshcd_keep_autobkops_enabled_except_suspend(hba))
		ufshcd_enable_auto_bkops(hba);
	else


		ufshcd_urgent_bkops(hba);

	hba->clk_gating.is_suspended = false;

	if (ufshcd_is_clkscaling_enabled(hba))
		devfreq_resume_device(hba->devfreq);


	ufshcd_release(hba);
	goto out;

set_old_link_state:
	ufshcd_link_state_transition(hba, old_link_state, 0);
vendor_suspend:
	ufshcd_vops_suspend(hba, pm_op);
disable_vreg:
	ufshcd_vreg_set_lpm(hba);
disable_irq_and_vops_clks:
	ufshcd_disable_irq(hba);
	ufshcd_setup_clocks(hba, false);
out:
	hba->pm_op_in_progress = 0;
	return ret;
}
