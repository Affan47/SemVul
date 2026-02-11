pnpacpi_disable_resources(struct pnp_dev *dev)
{
	struct acpi_device *acpi_dev;
	acpi_status status;

	dev_dbg(&dev->dev, "disable resources\n");

	acpi_dev = ACPI_COMPANION(&dev->dev);
	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		return 0;
	}


	if (acpi_device_power_manageable(acpi_dev))
		acpi_device_set_power(acpi_dev, ACPI_STATE_D3_COLD);


	status = acpi_evaluate_object(acpi_dev->handle, "_DIS", NULL, NULL);
	if (ACPI_FAILURE(status) && status != AE_NOT_FOUND)
		return -ENODEV;

	return 0;
}
