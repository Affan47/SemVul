msi_wmi_input_setup(void)
{
	int err;

	msi_wmi_input_dev = input_allocate_device();
	if (!msi_wmi_input_dev)
		return -ENOMEM;

	msi_wmi_input_dev->name = "MSI WMI hotkeys";
	msi_wmi_input_dev->phys = "wmi/input0";
	msi_wmi_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(msi_wmi_input_dev, msi_wmi_keymap, NULL);
	if (err)
		goto err_free_dev;

	err = input_register_device(msi_wmi_input_dev);

	if (err)
		goto err_free_keymap;

	last_pressed = ktime_set(0, 0);

	return 0;

err_free_keymap:
	sparse_keymap_free(msi_wmi_input_dev);
err_free_dev:
	input_free_device(msi_wmi_input_dev);
	return err;
}
