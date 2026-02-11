bttv_s_input(struct file *file, void *priv, unsigned int i)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	if (i >= bttv_tvcards[btv->c.type].video_inputs)
		return -EINVAL;

	set_input(btv, i, btv->tvnorm);
	return 0;
}
