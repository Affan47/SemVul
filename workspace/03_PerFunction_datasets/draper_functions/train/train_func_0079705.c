amdgpu_hwmon_show_temp(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	int temp;

	if (!adev->pp_enabled && !adev->pm.funcs->get_temperature)
		temp = 0;
	else
		temp = amdgpu_dpm_get_temperature(adev);

	return snprintf(buf, PAGE_SIZE, "%d\n", temp);
}
