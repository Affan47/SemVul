bios_enabled_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	acpi_status status;
	unsigned long long bios_enabled;

	status = acpi_evaluate_integer(NULL, BIOS_ENABLED, NULL, &bios_enabled);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	return sprintf(buf, "%s\n", bios_enabled ? "enabled" : "disabled");
}
