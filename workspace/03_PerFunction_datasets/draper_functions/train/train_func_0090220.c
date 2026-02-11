rfkill_init(struct platform_device *sdev)
{

	int retval;


	get_wireless_state_ec_standard();

	rfk_bluetooth = rfkill_alloc("msi-bluetooth", &sdev->dev,
				RFKILL_TYPE_BLUETOOTH,
				&rfkill_bluetooth_ops, NULL);
	if (!rfk_bluetooth) {
		retval = -ENOMEM;
		goto err_bluetooth;
	}
	retval = rfkill_register(rfk_bluetooth);
	if (retval)
		goto err_bluetooth;

	rfk_wlan = rfkill_alloc("msi-wlan", &sdev->dev, RFKILL_TYPE_WLAN,
				&rfkill_wlan_ops, NULL);
	if (!rfk_wlan) {
		retval = -ENOMEM;
		goto err_wlan;
	}
	retval = rfkill_register(rfk_wlan);
	if (retval)
		goto err_wlan;

	if (threeg_exists) {
		rfk_threeg = rfkill_alloc("msi-threeg", &sdev->dev,
				RFKILL_TYPE_WWAN, &rfkill_threeg_ops, NULL);
		if (!rfk_threeg) {
			retval = -ENOMEM;
			goto err_threeg;
		}
		retval = rfkill_register(rfk_threeg);
		if (retval)
			goto err_threeg;
	}


	if (quirks->ec_delay) {
		schedule_delayed_work(&msi_rfkill_init,
			round_jiffies_relative(1 * HZ));
	} else
		schedule_work(&msi_rfkill_work);

	return 0;

err_threeg:
	rfkill_destroy(rfk_threeg);
	if (rfk_wlan)
		rfkill_unregister(rfk_wlan);
err_wlan:
	rfkill_destroy(rfk_wlan);
	if (rfk_bluetooth)
		rfkill_unregister(rfk_bluetooth);
err_bluetooth:
	rfkill_destroy(rfk_bluetooth);

	return retval;
}
