irst_show_wakeup_time(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct acpi_device *acpi;
	unsigned long long value;
	acpi_status status;

	acpi = to_acpi_device(dev);

	status = acpi_evaluate_integer(acpi->handle, "GFTV", NULL, &value);
	if (ACPI_FAILURE(status))
		return -EINVAL;

	return sprintf(buf, "%lld\n", value);
}
