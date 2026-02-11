radio_g_tuner(struct file *file, void *priv, struct v4l2_tuner *t)
{
	struct cx231xx *dev = ((struct cx231xx_fh *)priv)->dev;

	if (t->index)
		return -EINVAL;

	strcpy(t->name, "Radio");

	call_all(dev, tuner, g_tuner, t);

	return 0;
}
