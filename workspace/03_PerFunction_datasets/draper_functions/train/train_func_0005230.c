ufshcd_force_reset_auto_bkops(struct ufs_hba *hba)
{
	if (ufshcd_keep_autobkops_enabled_except_suspend(hba)) {
		hba->auto_bkops_enabled = false;
		hba->ee_ctrl_mask |= MASK_EE_URGENT_BKOPS;
		ufshcd_enable_auto_bkops(hba);
	} else {
		hba->auto_bkops_enabled = true;
		hba->ee_ctrl_mask &= ~MASK_EE_URGENT_BKOPS;
		ufshcd_disable_auto_bkops(hba);
	}
}
