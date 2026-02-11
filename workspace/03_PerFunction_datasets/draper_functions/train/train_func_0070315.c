vidioc_s_audio(struct file *file, void *priv, const struct v4l2_audio *a)
{
	struct em28xx *dev = video_drvdata(file);

	if (a->index >= MAX_EM28XX_INPUT)
		return -EINVAL;
	if (0 == INPUT(a->index)->type)
		return -EINVAL;

	dev->ctl_ainput = INPUT(a->index)->amux;
	dev->ctl_aoutput = INPUT(a->index)->aout;

	if (!dev->ctl_aoutput)
		dev->ctl_aoutput = EM28XX_AOUT_MASTER;

	return 0;
}
