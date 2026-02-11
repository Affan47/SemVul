radio_s_tuner(struct file *file, void *priv,
					const struct v4l2_tuner *t)
{
	struct saa7134_dev *dev = video_drvdata(file);

	if (0 != t->index)
		return -EINVAL;

	saa_call_all(dev, tuner, s_tuner, t);
	return 0;
}
