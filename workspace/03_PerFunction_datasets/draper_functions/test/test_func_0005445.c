si476x_radio_enum_freq_bands(struct file *file, void *priv,
					struct v4l2_frequency_band *band)
{
	int err;
	struct si476x_radio *radio = video_drvdata(file);

	if (band->tuner != 0)
		return -EINVAL;

	switch (radio->core->chip_id) {

	case SI476X_CHIP_SI4761:
	case SI476X_CHIP_SI4764:
		if (band->index < ARRAY_SIZE(si476x_bands)) {
			*band = si476x_bands[band->index];
			err = 0;
		} else {
			err = -EINVAL;
		}
		break;


	case SI476X_CHIP_SI4768:
		if (band->index == SI476X_BAND_FM) {
			*band = si476x_bands[band->index];
			err = 0;
		} else {
			err = -EINVAL;
		}
		break;
	default:
		err = -EINVAL;
	}

	return err;
}
