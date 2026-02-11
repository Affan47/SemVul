acpi_manager_get_info(struct acpi_sbs *sbs)
{
	int result = 0;
	u16 battery_system_info;

	result = acpi_smbus_read(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_MANAGER,
				 0x04, (u8 *)&battery_system_info);
	if (!result)
		sbs->batteries_supported = battery_system_info & 0x000f;
	return result;
}
