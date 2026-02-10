usb_debugfs_init(void)
{
	usb_debug_root = debugfs_create_dir("usb", NULL);
	if (!usb_debug_root)
		return -ENOENT;

	usb_debug_devices = debugfs_create_file("devices", 0444,
						usb_debug_root, NULL,
						&usbfs_devices_fops);
	if (!usb_debug_devices) {
		debugfs_remove(usb_debug_root);
		usb_debug_root = NULL;
		return -ENOENT;
	}

	return 0;
}
