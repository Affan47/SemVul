s5p_jpeg_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *f)
{
	int ret;

	ret = s5p_jpeg_try_fmt_vid_out(file, priv, f);
	if (ret)
		return ret;

	return s5p_jpeg_s_fmt(fh_to_ctx(priv), f);
}
