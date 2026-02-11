sh_veu_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	const struct sh_veu_format *fmt;

	fmt = sh_veu_find_fmt(f);
	if (!fmt)

		return -EINVAL;

	return sh_veu_try_fmt(f, fmt);
}
