wm831x_backup_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *wm831x_pdata = wm831x->dev->platform_data;
	struct wm831x_backup *devdata;

	devdata = devm_kzalloc(&pdev->dev, sizeof(struct wm831x_backup),
				GFP_KERNEL);
	if (devdata == NULL)
		return -ENOMEM;

	devdata->wm831x = wm831x;
	platform_set_drvdata(pdev, devdata);


	wm831x_config_backup(wm831x);

	if (wm831x_pdata && wm831x_pdata->wm831x_num)
		snprintf(devdata->name, sizeof(devdata->name),
			 "wm831x-backup.%d", wm831x_pdata->wm831x_num);
	else
		snprintf(devdata->name, sizeof(devdata->name),
			 "wm831x-backup");

	devdata->backup_desc.name = devdata->name;
	devdata->backup_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	devdata->backup_desc.properties = wm831x_backup_props;
	devdata->backup_desc.num_properties = ARRAY_SIZE(wm831x_backup_props);
	devdata->backup_desc.get_property = wm831x_backup_get_prop;
	devdata->backup = power_supply_register(&pdev->dev,
						&devdata->backup_desc, NULL);

	return PTR_ERR_OR_ZERO(devdata->backup);
}
