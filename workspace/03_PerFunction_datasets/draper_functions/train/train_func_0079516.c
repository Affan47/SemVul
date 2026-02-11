vidioc_try_fmt(struct file *file, void *prv, struct v4l2_format *f)
{
	struct g2d_fmt *fmt;
	enum v4l2_field *field;

	fmt = find_fmt(f);
	if (!fmt)
		return -EINVAL;

	field = &f->fmt.pix.field;
	if (*field == V4L2_FIELD_ANY)
		*field = V4L2_FIELD_NONE;
	else if (*field != V4L2_FIELD_NONE)
		return -EINVAL;

	if (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	if (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	if (f->fmt.pix.width < 1)
		f->fmt.pix.width = 1;
	if (f->fmt.pix.height < 1)
		f->fmt.pix.height = 1;

	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	return 0;
}
