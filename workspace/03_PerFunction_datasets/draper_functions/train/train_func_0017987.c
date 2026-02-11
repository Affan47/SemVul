picolcd_init_devfs(struct picolcd_data *data,
		struct hid_report *eeprom_r, struct hid_report *eeprom_w,
		struct hid_report *flash_r, struct hid_report *flash_w,
		struct hid_report *reset)
{
	struct hid_device *hdev = data->hdev;

	mutex_init(&data->mutex_flash);


	if (reset)
		data->debug_reset = debugfs_create_file("reset", 0600,
				hdev->debug_dir, data, &picolcd_debug_reset_fops);


	if (eeprom_r || eeprom_w)
		data->debug_eeprom = debugfs_create_file("eeprom",
			(eeprom_w ? S_IWUSR : 0) | (eeprom_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_eeprom_fops);


	if (flash_r && flash_r->maxfield == 1 && flash_r->field[0]->report_size == 8)
		data->addr_sz = flash_r->field[0]->report_count - 1;
	else
		data->addr_sz = -1;
	if (data->addr_sz == 2 || data->addr_sz == 3) {
		data->debug_flash = debugfs_create_file("flash",
			(flash_w ? S_IWUSR : 0) | (flash_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_flash_fops);
	} else if (flash_r || flash_w)
		hid_warn(hdev, "Unexpected FLASH access reports, please submit rdesc for review\n");
}
