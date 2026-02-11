gsc_m2m_s_fmt_mplane(struct file *file, void *fh,
				 struct v4l2_format *f)
{
	struct gsc_ctx *ctx = fh_to_ctx(fh);
	struct vb2_queue *vq;
	struct gsc_frame *frame;
	struct v4l2_pix_format_mplane *pix;
	int i, ret = 0;

	ret = gsc_m2m_try_fmt_mplane(file, fh, f);
	if (ret)
		return ret;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);

	if (vb2_is_streaming(vq)) {
		pr_err("queue (%d) busy", f->type);
		return -EBUSY;
	}

	if (V4L2_TYPE_IS_OUTPUT(f->type))
		frame = &ctx->s_frame;
	else
		frame = &ctx->d_frame;

	pix = &f->fmt.pix_mp;
	frame->fmt = find_fmt(&pix->pixelformat, NULL, 0);
	frame->colorspace = pix->colorspace;
	if (!frame->fmt)
		return -EINVAL;

	for (i = 0; i < frame->fmt->num_planes; i++)
		frame->payload[i] = pix->plane_fmt[i].sizeimage;

	gsc_set_frame_size(frame, pix->width, pix->height);

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		gsc_ctx_state_lock_set(GSC_PARAMS | GSC_DST_FMT, ctx);
	else
		gsc_ctx_state_lock_set(GSC_PARAMS | GSC_SRC_FMT, ctx);

	pr_debug("f_w: %d, f_h: %d", frame->f_width, frame->f_height);

	return 0;
}
