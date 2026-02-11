apds990x_power_state_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	if (value) {
		pm_runtime_get_sync(dev);
		mutex_lock(&chip->mutex);
		chip->lux_wait_fresh_res = true;
		apds990x_force_a_refresh(chip);
		apds990x_force_p_refresh(chip);
		mutex_unlock(&chip->mutex);
	} else {
		if (!pm_runtime_suspended(dev))
			pm_runtime_put(dev);
	}
	return len;
}
