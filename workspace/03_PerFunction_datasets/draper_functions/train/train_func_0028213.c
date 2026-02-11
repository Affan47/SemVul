twl6040_vibra_close(struct input_dev *input)
{
	struct vibra_info *info = input_get_drvdata(input);

	cancel_work_sync(&info->play_work);

	mutex_lock(&info->mutex);

	if (info->enabled)
		twl6040_vibra_disable(info);

	mutex_unlock(&info->mutex);
}
