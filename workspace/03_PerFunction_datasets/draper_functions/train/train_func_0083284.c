vidioc_g_crop(struct file *file, void *prv, struct v4l2_crop *cr)
{
	struct g2d_ctx *ctx = prv;
	struct g2d_frame *f;

	f = get_frame(ctx, cr->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	cr->c.left	= f->o_height;
	cr->c.top	= f->o_width;
	cr->c.width	= f->c_width;
	cr->c.height	= f->c_height;
	return 0;
}
