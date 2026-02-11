vidioc_g_frequency(struct file *file, void *priv,
			      struct v4l2_frequency *f)
{
	struct em28xx         *dev = video_drvdata(file);
	struct em28xx_v4l2    *v4l2 = dev->v4l2;

	if (0 != f->tuner)
		return -EINVAL;

	f->frequency = v4l2->frequency;
	return 0;
}
