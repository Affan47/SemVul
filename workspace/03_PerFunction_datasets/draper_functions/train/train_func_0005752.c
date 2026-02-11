pincode_cb(struct agent *agent, DBusError *derr,
				const char *pincode, struct btd_device *device)
{
	struct btd_adapter *adapter = device_get_adapter(device);
	bdaddr_t dba;
	int err;

	device_get_address(device, &dba, NULL);

	if (derr) {
		err = btd_adapter_pincode_reply(adapter, &dba, NULL, 0);
		if (err < 0)
			goto fail;
		return;
	}

	err = btd_adapter_pincode_reply(adapter, &dba, pincode,
						pincode ? strlen(pincode) : 0);
	if (err < 0)
		goto fail;

	return;

fail:
	error("Sending PIN code reply failed: %s (%d)", strerror(-err), -err);
}
