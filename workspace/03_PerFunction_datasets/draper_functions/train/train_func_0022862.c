vibra_play(struct input_dev *input, void *data,
		      struct ff_effect *effect)
{
	struct vibra_info *info = input_get_drvdata(input);
	int ret;


	ret = twl6040_get_vibralr_status(info->twl6040);
	if (ret & TWL6040_VIBSEL) {
		dev_info(&input->dev, "Vibra is configured for audio\n");
		return -EBUSY;
	}

	info->weak_speed = effect->u.rumble.weak_magnitude;
	info->strong_speed = effect->u.rumble.strong_magnitude;
	info->direction = effect->direction < EFFECT_DIR_180_DEG ? 1 : -1;

	ret = queue_work(info->workqueue, &info->play_work);
	if (!ret) {
		dev_info(&input->dev, "work is already on queue\n");
		return ret;
	}

	return 0;
}
