ufshcd_parse_regulator_info(struct ufs_hba *hba)
{
	int err;
	struct device *dev = hba->dev;
	struct ufs_vreg_info *info = &hba->vreg_info;

	err = ufshcd_populate_vreg(dev, "vdd-hba", &info->vdd_hba);
	if (err)
		goto out;

	err = ufshcd_populate_vreg(dev, "vcc", &info->vcc);
	if (err)
		goto out;

	err = ufshcd_populate_vreg(dev, "vccq", &info->vccq);
	if (err)
		goto out;

	err = ufshcd_populate_vreg(dev, "vccq2", &info->vccq2);
out:
	return err;
}
