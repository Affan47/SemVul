rtl2832_sdr_g_frequency(struct file *file, void *priv,
		struct v4l2_frequency *f)
{
	struct rtl2832_sdr_dev *dev = video_drvdata(file);
	struct platform_device *pdev = dev->pdev;
	int ret;

	dev_dbg(&pdev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	if (f->tuner == 0) {
		f->frequency = dev->f_adc;
		f->type = V4L2_TUNER_ADC;
		ret = 0;
	} else if (f->tuner == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, g_frequency)) {
		f->type = V4L2_TUNER_RF;
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_frequency, f);
	} else if (f->tuner == 1) {
		f->frequency = dev->f_tuner;
		f->type = V4L2_TUNER_RF;
		ret = 0;
	} else {
		ret = -EINVAL;
	}
	return ret;
}
