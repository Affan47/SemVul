hidpp_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	struct hidpp_device *hidpp;
	int ret;
	bool connected;
	unsigned int connect_mask = HID_CONNECT_DEFAULT;

	hidpp = devm_kzalloc(&hdev->dev, sizeof(struct hidpp_device),
			GFP_KERNEL);
	if (!hidpp)
		return -ENOMEM;

	hidpp->hid_dev = hdev;
	hidpp->name = hdev->name;
	hid_set_drvdata(hdev, hidpp);

	hidpp->quirks = id->driver_data;

	if (disable_raw_mode) {
		hidpp->quirks &= ~HIDPP_QUIRK_CLASS_WTP;
		hidpp->quirks &= ~HIDPP_QUIRK_CONNECT_EVENTS;
		hidpp->quirks &= ~HIDPP_QUIRK_NO_HIDINPUT;
	}

	if (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP) {
		ret = wtp_allocate(hdev, id);
		if (ret)
			goto allocate_fail;
	} else if (hidpp->quirks & HIDPP_QUIRK_CLASS_M560) {
		ret = m560_allocate(hdev);
		if (ret)
			goto allocate_fail;
	} else if (hidpp->quirks & HIDPP_QUIRK_CLASS_K400) {
		ret = k400_allocate(hdev);
		if (ret)
			goto allocate_fail;
	}

	INIT_WORK(&hidpp->work, delayed_work_cb);
	mutex_init(&hidpp->send_mutex);
	init_waitqueue_head(&hidpp->wait);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "%s:parse failed\n", __func__);
		goto hid_parse_fail;
	}


	hid_device_io_start(hdev);

	connected = hidpp_is_connected(hidpp);
	if (id->group != HID_GROUP_LOGITECH_DJ_DEVICE) {
		if (!connected) {
			ret = -ENODEV;
			hid_err(hdev, "Device not connected");
			hid_device_io_stop(hdev);
			goto hid_parse_fail;
		}

		hid_info(hdev, "HID++ %u.%u device connected.\n",
			 hidpp->protocol_major, hidpp->protocol_minor);
	}

	hidpp_overwrite_name(hdev, id->group == HID_GROUP_LOGITECH_DJ_DEVICE);
	atomic_set(&hidpp->connected, connected);

	if (connected && (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)) {
		ret = wtp_get_config(hidpp);
		if (ret)
			goto hid_parse_fail;
	}


	hid_device_io_stop(hdev);

	if (hidpp->quirks & HIDPP_QUIRK_NO_HIDINPUT)
		connect_mask &= ~HID_CONNECT_HIDINPUT;

	ret = hid_hw_start(hdev, connect_mask);
	if (ret) {
		hid_err(hdev, "%s:hid_hw_start returned error\n", __func__);
		goto hid_hw_start_fail;
	}

	if (hidpp->quirks & HIDPP_QUIRK_CONNECT_EVENTS) {

		hid_device_io_start(hdev);

		hidpp_connect_event(hidpp);
	}

	return ret;

hid_hw_start_fail:
hid_parse_fail:
	cancel_work_sync(&hidpp->work);
	mutex_destroy(&hidpp->send_mutex);
allocate_fail:
	hid_set_drvdata(hdev, NULL);
	return ret;
}
