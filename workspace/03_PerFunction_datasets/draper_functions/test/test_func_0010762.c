acpi_scan_add_handler_with_hotplug(struct acpi_scan_handler *handler,
				       const char *hotplug_profile_name)
{
	int error;

	error = acpi_scan_add_handler(handler);
	if (error)
		return error;

	acpi_sysfs_add_hotplug_profile(&handler->hotplug, hotplug_profile_name);
	return 0;
}
