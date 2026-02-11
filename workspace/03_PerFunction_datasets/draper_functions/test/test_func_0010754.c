nouveau_hwmon_set_pwm1(struct device *d, struct device_attribute *a,
		       const char *buf, size_t count)
{
	struct drm_device *dev = dev_get_drvdata(d);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_therm *therm = nvxx_therm(&drm->device);
	int ret = -ENODEV;
	long value;

	if (kstrtol(buf, 10, &value) == -EINVAL)
		return -EINVAL;

	ret = therm->fan_set(therm, value);
	if (ret)
		return ret;

	return count;
}
