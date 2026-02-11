acpi_video_switch_brightness(struct work_struct *work)
{
	struct acpi_video_device *device = container_of(to_delayed_work(work),
			     struct acpi_video_device, switch_brightness_work);
	unsigned long long level_current, level_next;
	int event = device->switch_brightness_event;
	int result = -EINVAL;


	if (!device->backlight)
		return;

	if (!device->brightness)
		goto out;

	result = acpi_video_device_lcd_get_level_current(device,
							 &level_current,
							 false);
	if (result)
		goto out;

	level_next = acpi_video_get_next_level(device, level_current, event);

	result = acpi_video_device_lcd_set_level(device, level_next);

	if (!result)
		backlight_force_update(device->backlight,
				       BACKLIGHT_UPDATE_HOTKEY);

out:
	if (result)
		printk(KERN_ERR PREFIX "Failed to switch the brightness\n");
}
