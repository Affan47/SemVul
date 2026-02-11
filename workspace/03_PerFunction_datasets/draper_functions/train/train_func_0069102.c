appleir_probe(struct hid_device *hid, const struct hid_device_id *id)
{
	int ret;
	struct appleir *appleir;

	appleir = kzalloc(sizeof(struct appleir), GFP_KERNEL);
	if (!appleir) {
		ret = -ENOMEM;
		goto allocfail;
	}

	appleir->hid = hid;


	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;

	spin_lock_init(&appleir->lock);
	setup_timer(&appleir->key_up_timer,
		    key_up_tick, (unsigned long) appleir);

	hid_set_drvdata(hid, appleir);

	ret = hid_parse(hid);
	if (ret) {
		hid_err(hid, "parse failed\n");
		goto fail;
	}

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT | HID_CONNECT_HIDDEV_FORCE);
	if (ret) {
		hid_err(hid, "hw start failed\n");
		goto fail;
	}

	return 0;
fail:
	kfree(appleir);
allocfail:
	return ret;
}
