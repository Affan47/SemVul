vidioc_s_tuner(struct file *file, void *priv,
				const struct v4l2_tuner *v)
{
	struct ma901radio_device *radio = video_drvdata(file);

	if (v->index > 0)
		return -EINVAL;


	switch (v->audmode) {
	case V4L2_TUNER_MODE_MONO:
		return ma901_set_stereo(radio, MA901_WANT_MONO);
	default:
		return ma901_set_stereo(radio, MA901_WANT_STEREO);
	}
}
