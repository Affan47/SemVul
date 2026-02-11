b43legacy_probe(struct ssb_device *dev,
			 const struct ssb_device_id *id)
{
	struct b43legacy_wl *wl;
	int err;
	int first = 0;

	wl = ssb_get_devtypedata(dev);
	if (!wl) {

		first = 1;
		err = b43legacy_wireless_init(dev);
		if (err)
			goto out;
		wl = ssb_get_devtypedata(dev);
		B43legacy_WARN_ON(!wl);
	}
	err = b43legacy_one_core_attach(dev, wl);
	if (err)
		goto err_wireless_exit;


	INIT_WORK(&wl->firmware_load, b43legacy_request_firmware);
	schedule_work(&wl->firmware_load);

out:
	return err;

err_wireless_exit:
	if (first)
		b43legacy_wireless_exit(dev, wl);
	return err;
}
