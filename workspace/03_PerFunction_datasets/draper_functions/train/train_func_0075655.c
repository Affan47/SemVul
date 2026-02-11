dell_wmi_process_key(int reported_key)
{
	const struct key_entry *key;

	key = sparse_keymap_entry_from_scancode(dell_wmi_input_dev,
						reported_key);
	if (!key) {
		pr_info("Unknown key %x pressed\n", reported_key);
		return;
	}

	pr_debug("Key %x pressed\n", reported_key);


	if ((key->keycode == KEY_BRIGHTNESSUP ||
	     key->keycode == KEY_BRIGHTNESSDOWN) && acpi_video)
		return;

	sparse_keymap_report_entry(dell_wmi_input_dev, key, 1, true);
}
