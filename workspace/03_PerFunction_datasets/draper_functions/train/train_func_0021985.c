asus_sysfs_is_visible(struct kobject *kobj,
				    struct attribute *attr, int idx)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct platform_device *pdev = to_platform_device(dev);
	struct asus_wmi *asus = platform_get_drvdata(pdev);
	bool ok = true;
	int devid = -1;

	if (attr == &dev_attr_camera.attr)
		devid = ASUS_WMI_DEVID_CAMERA;
	else if (attr == &dev_attr_cardr.attr)
		devid = ASUS_WMI_DEVID_CARDREADER;
	else if (attr == &dev_attr_touchpad.attr)
		devid = ASUS_WMI_DEVID_TOUCHPAD;
	else if (attr == &dev_attr_lid_resume.attr)
		devid = ASUS_WMI_DEVID_LID_RESUME;

	if (devid != -1)
		ok = !(asus_wmi_get_devstate_simple(asus, devid) < 0);

	return ok ? attr->mode : 0;
}
