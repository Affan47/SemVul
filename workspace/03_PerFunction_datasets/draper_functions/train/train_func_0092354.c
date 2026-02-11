hp_wireless_input_setup(void)
{
	int err;

	hpwl_input_dev = input_allocate_device();
	if (!hpwl_input_dev)
		return -ENOMEM;

	hpwl_input_dev->name = "HP Wireless hotkeys";
	hpwl_input_dev->phys = "hpq6001/input0";
	hpwl_input_dev->id.bustype = BUS_HOST;
	hpwl_input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_RFKILL, hpwl_input_dev->keybit);

	err = input_register_device(hpwl_input_dev);
	if (err)
		goto err_free_dev;

	return 0;

err_free_dev:
	input_free_device(hpwl_input_dev);
	return err;
}
