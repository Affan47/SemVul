acpi_fujitsu_notify(struct acpi_device *device, u32 event)
{
	struct input_dev *input;
	int keycode;
	int oldb, newb;

	input = fujitsu->input;

	switch (event) {
	case ACPI_FUJITSU_NOTIFY_CODE1:
		keycode = 0;
		oldb = fujitsu->brightness_level;
		get_lcd_level();
		newb = fujitsu->brightness_level;

		vdbg_printk(FUJLAPTOP_DBG_TRACE,
			    "brightness button event [%i -> %i (%i)]\n",
			    oldb, newb, fujitsu->brightness_changed);

		if (oldb < newb) {
			if (disable_brightness_adjust != 1) {
				if (use_alt_lcd_levels)
					set_lcd_level_alt(newb);
				else
					set_lcd_level(newb);
			}
			keycode = KEY_BRIGHTNESSUP;
		} else if (oldb > newb) {
			if (disable_brightness_adjust != 1) {
				if (use_alt_lcd_levels)
					set_lcd_level_alt(newb);
				else
					set_lcd_level(newb);
			}
			keycode = KEY_BRIGHTNESSDOWN;
		}
		break;
	default:
		keycode = KEY_UNKNOWN;
		vdbg_printk(FUJLAPTOP_DBG_WARN,
			    "unsupported event [0x%x]\n", event);
		break;
	}

	if (keycode != 0) {
		input_report_key(input, keycode, 1);
		input_sync(input);
		input_report_key(input, keycode, 0);
		input_sync(input);
	}
}
