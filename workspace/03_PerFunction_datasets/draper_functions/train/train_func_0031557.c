dell_wmi_init(void)
{
	int err;
	acpi_status status;

	if (!wmi_has_guid(DELL_EVENT_GUID)) {
		pr_warn("No known WMI GUID found\n");
		return -ENODEV;
	}

	dmi_walk(find_hk_type, NULL);
	acpi_video = acpi_video_get_backlight_type() != acpi_backlight_vendor;

	err = dell_wmi_input_setup();
	if (err)
		return err;

	status = wmi_install_notify_handler(DELL_EVENT_GUID,
					 dell_wmi_notify, NULL);
	if (ACPI_FAILURE(status)) {
		dell_wmi_input_destroy();
		pr_err("Unable to register notify handler - %d\n", status);
		return -ENODEV;
	}

	return 0;
}
