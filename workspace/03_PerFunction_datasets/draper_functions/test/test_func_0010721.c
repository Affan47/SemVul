__max77693_led_brightness_set(struct max77693_led_device *led,
					int fled_id, enum led_brightness value)
{
	int ret;

	mutex_lock(&led->lock);

	if (value == 0) {
		ret = max77693_clear_mode(led, MODE_TORCH(fled_id));
		if (ret < 0)
			dev_dbg(&led->pdev->dev,
				"Failed to clear torch mode (%d)\n",
				ret);
		goto unlock;
	}

	ret = max77693_set_torch_current(led, fled_id, value * TORCH_IOUT_STEP);
	if (ret < 0) {
		dev_dbg(&led->pdev->dev,
			"Failed to set torch current (%d)\n",
			ret);
		goto unlock;
	}

	ret = max77693_add_mode(led, MODE_TORCH(fled_id));
	if (ret < 0)
		dev_dbg(&led->pdev->dev,
			"Failed to set torch mode (%d)\n",
			ret);
unlock:
	mutex_unlock(&led->lock);
	return ret;
}
