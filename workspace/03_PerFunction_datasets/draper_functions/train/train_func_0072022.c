tuner_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct tuner *t = to_tuner(sd);

	if (set_mode(t, vt->type))
		return 0;

	if (t->mode == V4L2_TUNER_RADIO) {
		t->audmode = vt->audmode;


		if (t->audmode != V4L2_TUNER_MODE_MONO &&
		    t->audmode != V4L2_TUNER_MODE_STEREO)
			t->audmode = V4L2_TUNER_MODE_STEREO;
	}
	set_freq(t, 0);

	return 0;
}
