vidioc_g_fmt(struct deinterlace_ctx *ctx, struct v4l2_format *f)
{
	struct vb2_queue *vq;
	struct deinterlace_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = get_q_data(f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= q_data->field;
	f->fmt.pix.pixelformat	= q_data->fmt->fourcc;

	switch (q_data->fmt->fourcc) {
	case V4L2_PIX_FMT_YUV420:
		f->fmt.pix.bytesperline = q_data->width * 3 / 2;
		break;
	case V4L2_PIX_FMT_YUYV:
	default:
		f->fmt.pix.bytesperline = q_data->width * 2;
	}

	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.colorspace	= ctx->colorspace;

	return 0;
}
