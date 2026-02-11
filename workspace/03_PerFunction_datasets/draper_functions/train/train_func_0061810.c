exynos4_jpeg_get_output_buffer_size(struct s5p_jpeg_ctx *ctx,
						struct v4l2_format *f,
						int fmt_depth)
{
	struct v4l2_pix_format *pix = &f->fmt.pix;
	u32 pix_fmt = f->fmt.pix.pixelformat;
	int w = pix->width, h = pix->height, wh_align;

	if (pix_fmt == V4L2_PIX_FMT_RGB32 ||
	    pix_fmt == V4L2_PIX_FMT_NV24 ||
	    pix_fmt == V4L2_PIX_FMT_NV42 ||
	    pix_fmt == V4L2_PIX_FMT_NV12 ||
	    pix_fmt == V4L2_PIX_FMT_NV21 ||
	    pix_fmt == V4L2_PIX_FMT_YUV420)
		wh_align = 4;
	else
		wh_align = 1;

	jpeg_bound_align_image(ctx, &w, S5P_JPEG_MIN_WIDTH,
			       S5P_JPEG_MAX_WIDTH, wh_align,
			       &h, S5P_JPEG_MIN_HEIGHT,
			       S5P_JPEG_MAX_HEIGHT, wh_align);

	return w * h * fmt_depth >> 3;
}
