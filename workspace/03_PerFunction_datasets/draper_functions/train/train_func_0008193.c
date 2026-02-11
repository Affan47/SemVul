device_rtc_init(struct pm860x_chip *chip,
				      struct pm860x_platform_data *pdata)
{
	int ret;

	if (!pdata)
		return;

	rtc_devs[0].platform_data = pdata->rtc;
	rtc_devs[0].pdata_size = sizeof(struct pm860x_rtc_pdata);
	rtc_devs[0].num_resources = ARRAY_SIZE(rtc_resources);
	rtc_devs[0].resources = &rtc_resources[0];
	ret = mfd_add_devices(chip->dev, 0, &rtc_devs[0],
			      ARRAY_SIZE(rtc_devs), &rtc_resources[0],
			      chip->irq_base, NULL);
	if (ret < 0)
		dev_err(chip->dev, "Failed to add rtc subdev\n");
}
