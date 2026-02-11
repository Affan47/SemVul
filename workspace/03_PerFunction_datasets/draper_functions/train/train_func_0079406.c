bttv_s_tuner(struct file *file, void *priv,
					const struct v4l2_tuner *t)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	if (t->index)
		return -EINVAL;

	bttv_call_all(btv, tuner, s_tuner, t);

	if (btv->audio_mode_gpio) {
		struct v4l2_tuner copy = *t;

		btv->audio_mode_gpio(btv, &copy, 1);
	}
	return 0;
}
