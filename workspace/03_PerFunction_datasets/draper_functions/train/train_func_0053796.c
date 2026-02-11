vivid_video_s_tuner(struct file *file, void *fh, const struct v4l2_tuner *vt)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (vt->index != 0)
		return -EINVAL;
	if (vt->audmode > V4L2_TUNER_MODE_LANG1_LANG2)
		return -EINVAL;
	dev->tv_audmode = vt->audmode;
	return 0;
}
