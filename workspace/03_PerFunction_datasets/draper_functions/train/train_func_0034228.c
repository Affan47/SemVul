bttv_cropcap(struct file *file, void *priv,
				struct v4l2_cropcap *cap)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (cap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    cap->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	*cap = bttv_tvnorms[btv->tvnorm].cropcap;

	return 0;
}
