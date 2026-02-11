update_devfreq(struct devfreq *devfreq)
{
	unsigned long freq;
	int err = 0;
	u32 flags = 0;

	if (!mutex_is_locked(&devfreq->lock)) {
		WARN(true, "devfreq->lock must be locked by the caller.\n");
		return -EINVAL;
	}

	if (!devfreq->governor)
		return -EINVAL;


	err = devfreq->governor->get_target_freq(devfreq, &freq);
	if (err)
		return err;


	if (devfreq->min_freq && freq < devfreq->min_freq) {
		freq = devfreq->min_freq;
		flags &= ~DEVFREQ_FLAG_LEAST_UPPER_BOUND;
	}
	if (devfreq->max_freq && freq > devfreq->max_freq) {
		freq = devfreq->max_freq;
		flags |= DEVFREQ_FLAG_LEAST_UPPER_BOUND;
	}

	err = devfreq->profile->target(devfreq->dev.parent, &freq, flags);
	if (err)
		return err;

	if (devfreq->profile->freq_table)
		if (devfreq_update_status(devfreq, freq))
			dev_err(&devfreq->dev,
				"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = freq;
	return err;
}
