s5p_jpeg_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	if (ctx->mode == S5P_JPEG_ENCODE) {
		strlcpy(cap->driver, S5P_JPEG_M2M_NAME " encoder",
			sizeof(cap->driver));
		strlcpy(cap->card, S5P_JPEG_M2M_NAME " encoder",
			sizeof(cap->card));
	} else {
		strlcpy(cap->driver, S5P_JPEG_M2M_NAME " decoder",
			sizeof(cap->driver));
		strlcpy(cap->card, S5P_JPEG_M2M_NAME " decoder",
			sizeof(cap->card));
	}
	cap->bus_info[0] = 0;
	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}
