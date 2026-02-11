acpi_ut_interface_terminate(void)
{
	acpi_status status;
	struct acpi_interface_info *next_interface;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	next_interface = acpi_gbl_supported_interfaces;
	while (next_interface) {
		acpi_gbl_supported_interfaces = next_interface->next;

		if (next_interface->flags & ACPI_OSI_DYNAMIC) {


			ACPI_FREE(next_interface->name);
			ACPI_FREE(next_interface);
		} else {


			if (next_interface->flags & ACPI_OSI_DEFAULT_INVALID) {
				next_interface->flags |= ACPI_OSI_INVALID;
			} else {
				next_interface->flags &= ~ACPI_OSI_INVALID;
			}
		}

		next_interface = acpi_gbl_supported_interfaces;
	}

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	return (AE_OK);
}
