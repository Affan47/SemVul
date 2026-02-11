wiimote_hid_probe(struct hid_device *hdev,
				const struct hid_device_id *id)
{
	struct wiimote_data *wdata;
	int ret;

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	wdata = wiimote_create(hdev);
	if (!wdata) {
		hid_err(hdev, "Can't alloc device\n");
		return -ENOMEM;
	}

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "HID parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	if (ret) {
		hid_err(hdev, "HW start failed\n");
		goto err;
	}

	ret = hid_hw_open(hdev);
	if (ret) {
		hid_err(hdev, "cannot start hardware I/O\n");
		goto err_stop;
	}

	ret = device_create_file(&hdev->dev, &dev_attr_extension);
	if (ret) {
		hid_err(hdev, "cannot create sysfs attribute\n");
		goto err_close;
	}

	ret = device_create_file(&hdev->dev, &dev_attr_devtype);
	if (ret) {
		hid_err(hdev, "cannot create sysfs attribute\n");
		goto err_ext;
	}

	ret = wiidebug_init(wdata);
	if (ret)
		goto err_free;

	hid_info(hdev, "New device registered\n");


	wiimote_schedule(wdata);

	return 0;

err_free:
	wiimote_destroy(wdata);
	return ret;

err_ext:
	device_remove_file(&wdata->hdev->dev, &dev_attr_extension);
err_close:
	hid_hw_close(hdev);
err_stop:
	hid_hw_stop(hdev);
err:
	input_free_device(wdata->ir);
	input_free_device(wdata->accel);
	kfree(wdata);
	return ret;
}
