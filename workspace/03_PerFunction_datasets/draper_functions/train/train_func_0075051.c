radeon_hwmon_get_pwm1(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct radeon_device *rdev = dev_get_drvdata(dev);
	int err;
	u32 speed;

	err = rdev->asic->dpm.get_fan_speed_percent(rdev, &speed);
	if (err)
		return err;

	speed = (speed * 255) / 100;

	return sprintf(buf, "%i\n", speed);
}
