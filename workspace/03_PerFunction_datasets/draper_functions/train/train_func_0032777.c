verify_preview(struct saa7134_dev *dev, struct v4l2_window *win, bool try)
{
	enum v4l2_field field;
	int maxw, maxh;

	if (!try && (dev->ovbuf.base == NULL || dev->ovfmt == NULL))
		return -EINVAL;
	if (win->w.width < 48)
		win->w.width = 48;
	if (win->w.height < 32)
		win->w.height = 32;
	if (win->clipcount > 8)
		win->clipcount = 8;

	win->chromakey = 0;
	win->global_alpha = 0;
	field = win->field;
	maxw  = dev->crop_current.width;
	maxh  = dev->crop_current.height;

	if (V4L2_FIELD_ANY == field) {
		field = (win->w.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	}
	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		break;
	default:
		field = V4L2_FIELD_INTERLACED;
		break;
	}

	win->field = field;
	if (win->w.width > maxw)
		win->w.width = maxw;
	if (win->w.height > maxh)
		win->w.height = maxh;
	return 0;
}
