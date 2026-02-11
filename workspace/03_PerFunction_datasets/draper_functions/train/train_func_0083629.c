radio_s_hw_freq_seek(struct file *file, void *priv,
					const struct v4l2_hw_freq_seek *a)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (btv->has_tea575x)
		return snd_tea575x_s_hw_freq_seek(file, &btv->tea, a);

	return -ENOTTY;
}
