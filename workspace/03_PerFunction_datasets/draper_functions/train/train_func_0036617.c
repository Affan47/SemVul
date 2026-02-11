vivid_sdr_g_frequency(struct file *file, void *fh,
		struct v4l2_frequency *vf)
{
	struct vivid_dev *dev = video_drvdata(file);

	switch (vf->tuner) {
	case 0:
		vf->frequency = dev->sdr_adc_freq;
		vf->type = V4L2_TUNER_ADC;
		return 0;
	case 1:
		vf->frequency = dev->sdr_fm_freq;
		vf->type = V4L2_TUNER_RF;
		return 0;
	default:
		return -EINVAL;
	}
}
