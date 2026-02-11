si470x_set_seek(struct si470x_device *radio,
			   const struct v4l2_hw_freq_seek *seek)
{
	int band, retval;
	unsigned int freq;
	bool timed_out = false;
	unsigned long time_left;


	if (seek->rangelow || seek->rangehigh) {
		for (band = 0; band < ARRAY_SIZE(bands); band++) {
			if (bands[band].rangelow  == seek->rangelow &&
			    bands[band].rangehigh == seek->rangehigh)
				break;
		}
		if (band == ARRAY_SIZE(bands))
			return -EINVAL;
	} else
		band = 1;

	if (radio->band != band) {
		retval = si470x_get_freq(radio, &freq);
		if (retval)
			return retval;
		retval = si470x_set_band(radio, band);
		if (retval)
			return retval;
		retval = si470x_set_freq(radio, freq);
		if (retval)
			return retval;
	}


	radio->registers[POWERCFG] |= POWERCFG_SEEK;
	if (seek->wrap_around)
		radio->registers[POWERCFG] &= ~POWERCFG_SKMODE;
	else
		radio->registers[POWERCFG] |= POWERCFG_SKMODE;
	if (seek->seek_upward)
		radio->registers[POWERCFG] |= POWERCFG_SEEKUP;
	else
		radio->registers[POWERCFG] &= ~POWERCFG_SEEKUP;
	retval = si470x_set_register(radio, POWERCFG);
	if (retval < 0)
		return retval;


	reinit_completion(&radio->completion);
	time_left = wait_for_completion_timeout(&radio->completion,
						msecs_to_jiffies(seek_timeout));
	if (time_left == 0)
		timed_out = true;

	if ((radio->registers[STATUSRSSI] & STATUSRSSI_STC) == 0)
		dev_warn(&radio->videodev.dev, "seek does not complete\n");
	if (radio->registers[STATUSRSSI] & STATUSRSSI_SF)
		dev_warn(&radio->videodev.dev,
			"seek failed / band limit reached\n");


	radio->registers[POWERCFG] &= ~POWERCFG_SEEK;
	retval = si470x_set_register(radio, POWERCFG);


	if (retval == 0 && timed_out)
		return -ENODATA;
	return retval;
}
