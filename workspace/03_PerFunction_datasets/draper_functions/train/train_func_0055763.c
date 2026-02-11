acpi_video_get_backlight_type(void)
{
	static DEFINE_MUTEX(init_mutex);
	static bool init_done;
	static long video_caps;


	mutex_lock(&init_mutex);
	if (!init_done) {
		acpi_video_parse_cmdline();
		dmi_check_system(video_detect_dmi_table);
		acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				    ACPI_UINT32_MAX, find_video, NULL,
				    &video_caps, NULL);
		INIT_WORK(&backlight_notify_work,
			  acpi_video_backlight_notify_work);
		backlight_nb.notifier_call = acpi_video_backlight_notify;
		backlight_nb.priority = 0;
		if (backlight_register_notifier(&backlight_nb) == 0)
			backlight_notifier_registered = true;
		init_done = true;
	}
	mutex_unlock(&init_mutex);

	if (acpi_backlight_cmdline != acpi_backlight_undef)
		return acpi_backlight_cmdline;

	if (acpi_backlight_dmi != acpi_backlight_undef)
		return acpi_backlight_dmi;

	if (!(video_caps & ACPI_VIDEO_BACKLIGHT))
		return acpi_backlight_vendor;

	if (acpi_osi_is_win8() && backlight_device_registered(BACKLIGHT_RAW))
		return acpi_backlight_native;

	return acpi_backlight_video;
}
