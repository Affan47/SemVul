acpi_db_display_interfaces(char *action_arg, char *interface_name_arg)
{
	struct acpi_interface_info *next_interface;
	char *sub_string;
	acpi_status status;


	if (!action_arg) {
		(void)acpi_os_acquire_mutex(acpi_gbl_osi_mutex,
					    ACPI_WAIT_FOREVER);

		next_interface = acpi_gbl_supported_interfaces;
		while (next_interface) {
			if (!(next_interface->flags & ACPI_OSI_INVALID)) {
				acpi_os_printf("%s\n", next_interface->name);
			}

			next_interface = next_interface->next;
		}

		acpi_os_release_mutex(acpi_gbl_osi_mutex);
		return;
	}


	if (!interface_name_arg) {
		acpi_os_printf("Missing Interface Name argument\n");
		return;
	}


	acpi_ut_strupr(action_arg);


	sub_string = strstr("INSTALL", action_arg);
	if (sub_string) {
		status = acpi_install_interface(interface_name_arg);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("%s, while installing \"%s\"\n",
				       acpi_format_exception(status),
				       interface_name_arg);
		}
		return;
	}


	sub_string = strstr("REMOVE", action_arg);
	if (sub_string) {
		status = acpi_remove_interface(interface_name_arg);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("%s, while removing \"%s\"\n",
				       acpi_format_exception(status),
				       interface_name_arg);
		}
		return;
	}


	acpi_os_printf("Invalid action argument: %s\n", action_arg);
	return;
}
