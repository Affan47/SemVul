usbfbus_connect_request(struct gn_statemachine *state)
{
	int ret;

	DEVINSTANCE(state)->interface->dev_data = usb_open(DEVINSTANCE(state)->interface->device);

	ret = usb_set_configuration(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->configuration);
	if (ret < 0) {
		dprintf("Can't set configuration: %d\n", ret);
	}

	ret = usb_claim_interface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->control_interface);
	if (ret < 0) {
		dprintf("Can't claim control interface: %d\n", ret);
		goto err1;
	}

	ret = usb_set_altinterface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->control_setting);
	if (ret < 0) {
		dprintf("Can't set control setting: %d\n", ret);
		goto err2;
	}

	ret = usb_claim_interface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->data_interface);
	if (ret < 0) {
		dprintf("Can't claim data interface: %d\n", ret);
		goto err2;
	}

	ret = usb_set_altinterface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->data_active_setting);
	if (ret < 0) {
		dprintf("Can't set data active setting: %d\n", ret);
		goto err3;
	}
	return 1;

err3:
	usb_release_interface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->data_interface);
err2:
	usb_release_interface(DEVINSTANCE(state)->interface->dev_data, DEVINSTANCE(state)->interface->control_interface);
err1:
	usb_close(DEVINSTANCE(state)->interface->dev_data);
	return 0;
}
