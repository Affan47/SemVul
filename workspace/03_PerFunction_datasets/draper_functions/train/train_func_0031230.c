ufshcd_variant_hba_exit(struct ufs_hba *hba)
{
	if (!hba->vops)
		return;

	ufshcd_vops_setup_clocks(hba, false);

	ufshcd_vops_setup_regulators(hba, false);

	ufshcd_vops_exit(hba);
}
