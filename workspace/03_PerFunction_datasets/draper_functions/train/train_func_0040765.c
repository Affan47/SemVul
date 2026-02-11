saa7134_s_tuner(struct file *file, void *priv,
					const struct v4l2_tuner *t)
{
	struct saa7134_dev *dev = video_drvdata(file);
	int rx, mode;

	if (0 != t->index)
		return -EINVAL;

	mode = dev->thread.mode;
	if (UNSET == mode) {
		rx   = saa7134_tvaudio_getstereo(dev);
		mode = saa7134_tvaudio_rx2mode(rx);
	}
	if (mode != t->audmode)
		dev->thread.mode = t->audmode;

	return 0;
}
