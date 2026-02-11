drv260x_suspend(struct device *dev)
{
	struct drv260x_data *haptics = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	if (haptics->input_dev->users) {
		ret = regmap_update_bits(haptics->regmap,
					 DRV260X_MODE,
					 DRV260X_STANDBY_MASK,
					 DRV260X_STANDBY);
		if (ret) {
			dev_err(dev, "Failed to set standby mode\n");
			goto out;
		}

		gpiod_set_value(haptics->enable_gpio, 0);

		ret = regulator_disable(haptics->regulator);
		if (ret) {
			dev_err(dev, "Failed to disable regulator\n");
			regmap_update_bits(haptics->regmap,
					   DRV260X_MODE,
					   DRV260X_STANDBY_MASK, 0);
		}
	}
out:
	mutex_unlock(&haptics->input_dev->mutex);
	return ret;
}
