intel_hid_set_enable(struct device *device, int enable)
{
	union acpi_object arg0 = { ACPI_TYPE_INTEGER };
	struct acpi_object_list args = { 1, &arg0 };
	acpi_status status;

	arg0.integer.value = enable;
	status = acpi_evaluate_object(ACPI_HANDLE(device), "HDSM", &args, NULL);
	if (!ACPI_SUCCESS(status)) {
		dev_warn(device, "failed to %sable hotkeys\n",
			 enable ? "en" : "dis");
		return -EIO;
	}

	return 0;
}
