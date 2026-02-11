vt1211_remove_sysfs(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int i;

	for (i = 0; i < ARRAY_SIZE(vt1211_in_attr_group); i++)
		sysfs_remove_group(&dev->kobj, &vt1211_in_attr_group[i]);

	for (i = 0; i < ARRAY_SIZE(vt1211_temp_attr_group); i++)
		sysfs_remove_group(&dev->kobj, &vt1211_temp_attr_group[i]);

	for (i = 0; i < ARRAY_SIZE(vt1211_sysfs_fan_pwm); i++) {
		device_remove_file(dev,
			&vt1211_sysfs_fan_pwm[i].dev_attr);
	}
	for (i = 0; i < ARRAY_SIZE(vt1211_sysfs_misc); i++)
		device_remove_file(dev, &vt1211_sysfs_misc[i]);
}
