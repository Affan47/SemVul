acpi_sbs_resume(struct device *dev)
{
	struct acpi_sbs *sbs;
	if (!dev)
		return -EINVAL;
	sbs = to_acpi_device(dev)->driver_data;
	acpi_sbs_callback(sbs);
	return 0;
}
