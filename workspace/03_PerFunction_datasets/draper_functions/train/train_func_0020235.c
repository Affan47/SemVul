ide_acpi_set_state(ide_hwif_t *hwif, int on)
{
	ide_drive_t *drive;
	int i;

	if (ide_noacpi_psx)
		return;

	DEBPRINT("ENTER:\n");


	if (on)
		acpi_bus_set_power(hwif->acpidata->obj_handle, ACPI_STATE_D0);

	ide_port_for_each_present_dev(i, drive, hwif) {
		if (drive->acpidata->obj_handle)
			acpi_bus_set_power(drive->acpidata->obj_handle,
				on ? ACPI_STATE_D0 : ACPI_STATE_D3_COLD);
	}

	if (!on)
		acpi_bus_set_power(hwif->acpidata->obj_handle,
				   ACPI_STATE_D3_COLD);
}
