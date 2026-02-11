tda9840_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *t)
{
	int stat = tda9840_status(sd);

	if (stat < 0)
		return stat;

	t->rxsubchans = V4L2_TUNER_SUB_MONO;

	switch (stat & 0x60) {
	case 0x00:
		t->rxsubchans = V4L2_TUNER_SUB_MONO;
		break;
	case 0x20:
		t->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		break;
	case 0x40:
		t->rxsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_MONO;
		break;
	default:
		t->rxsubchans = V4L2_TUNER_MODE_MONO;
		break;
	}
	return 0;
}
