input_ff_create(struct input_dev *dev, unsigned int max_effects)
{
	struct ff_device *ff;
	size_t ff_dev_size;
	int i;

	if (!max_effects) {
		dev_err(&dev->dev, "cannot allocate device without any effects\n");
		return -EINVAL;
	}

	if (max_effects > FF_MAX_EFFECTS) {
		dev_err(&dev->dev, "cannot allocate more than FF_MAX_EFFECTS effects\n");
		return -EINVAL;
	}

	ff_dev_size = sizeof(struct ff_device) +
				max_effects * sizeof(struct file *);
	if (ff_dev_size < max_effects)
		return -EINVAL;

	ff = kzalloc(ff_dev_size, GFP_KERNEL);
	if (!ff)
		return -ENOMEM;

	ff->effects = kcalloc(max_effects, sizeof(struct ff_effect),
			      GFP_KERNEL);
	if (!ff->effects) {
		kfree(ff);
		return -ENOMEM;
	}

	ff->max_effects = max_effects;
	mutex_init(&ff->mutex);

	dev->ff = ff;
	dev->flush = flush_effects;
	dev->event = input_ff_event;
	__set_bit(EV_FF, dev->evbit);


	for_each_set_bit(i, dev->ffbit, FF_CNT)
		__set_bit(i, ff->ffbit);


	if (test_bit(FF_PERIODIC, ff->ffbit))
		__set_bit(FF_RUMBLE, dev->ffbit);

	return 0;
}
