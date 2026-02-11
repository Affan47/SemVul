fimc_m2m_set_default_format(struct fimc_ctx *ctx)
{
	struct v4l2_pix_format_mplane pixm = {
		.pixelformat	= V4L2_PIX_FMT_RGB32,
		.width		= 800,
		.height		= 600,
		.plane_fmt[0]	= {
			.bytesperline = 800 * 4,
			.sizeimage = 800 * 4 * 600,
		},
	};
	struct fimc_fmt *fmt;

	fmt = fimc_find_format(&pixm.pixelformat, NULL, FMT_FLAGS_M2M, 0);
	if (!fmt)
		return -EINVAL;

	__set_frame_format(&ctx->s_frame, fmt, &pixm);
	__set_frame_format(&ctx->d_frame, fmt, &pixm);

	return 0;
}
