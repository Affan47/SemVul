acpi_lpss_runtime_resume(struct device *dev)
{
	struct lpss_private_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	int ret;


	if (lpss_quirks & LPSS_QUIRK_ALWAYS_POWER_ON && iosf_mbi_available())
		lpss_iosf_exit_d3_state();

	ret = acpi_dev_runtime_resume(dev);
	if (ret)
		return ret;

	if (pdata->dev_desc->flags & LPSS_SAVE_CTX)
		acpi_lpss_restore_ctx(dev, pdata);

	return pm_generic_runtime_resume(dev);
}
