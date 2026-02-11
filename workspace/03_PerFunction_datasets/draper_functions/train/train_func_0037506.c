sony_nc_battery_care_cleanup(struct platform_device *pd)
{
	if (bcare_ctl) {
		device_remove_file(&pd->dev, &bcare_ctl->attrs[0]);
		if (bcare_ctl->handle != 0x0115)
			device_remove_file(&pd->dev, &bcare_ctl->attrs[1]);

		kfree(bcare_ctl);
		bcare_ctl = NULL;
	}
}
