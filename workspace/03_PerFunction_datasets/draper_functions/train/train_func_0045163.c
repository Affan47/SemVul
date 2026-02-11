eeepc_wmi_check_atkd(void)
{
	acpi_status status;
	bool found = false;

	status = acpi_get_devices(EEEPC_ACPI_HID, eeepc_wmi_parse_device,
				  &found, NULL);

	if (ACPI_FAILURE(status) || !found)
		return 0;
	return -1;
}
