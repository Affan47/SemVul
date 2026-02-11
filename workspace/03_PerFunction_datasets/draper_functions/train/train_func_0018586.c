hotkey_resume(void)
{
	tpacpi_disable_brightness_delay();

	if (hotkey_status_set(true) < 0 ||
	    hotkey_mask_set(hotkey_acpi_mask) < 0)
		pr_err("error while attempting to reset the event "
		       "firmware interface\n");

	tpacpi_send_radiosw_update();
	hotkey_tablet_mode_notify_change();
	hotkey_wakeup_reason_notify_change();
	hotkey_wakeup_hotunplug_complete_notify_change();
	hotkey_poll_setup_safe(false);


	if (tp_features.has_adaptive_kbd) {
		if (!acpi_evalf(hkey_handle, NULL, "STRW", "vd",
					adaptive_keyboard_prev_mode)) {
			pr_err("Cannot set adaptive keyboard mode.\n");
		}
	}
}
