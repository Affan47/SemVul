avermedia_tv_stereo_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	int val = 0;

	if (!set) {

		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		return;
	}

	switch (t->audmode) {
	case V4L2_TUNER_MODE_LANG2:
		val = 0x01;
		break;
	case V4L2_TUNER_MODE_STEREO:
		val = 0x02;
		break;
	default:
		val = 0;
		break;
	}
	btaor(val, ~0x03, BT848_GPIO_DATA);
	if (bttv_gpio)
		bttv_gpio_tracking(btv, "avermedia");
}
