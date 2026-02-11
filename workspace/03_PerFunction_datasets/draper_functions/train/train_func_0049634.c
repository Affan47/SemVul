bttv_enum_fmt_vid_overlay(struct file *file, void  *priv,
					struct v4l2_fmtdesc *f)
{
	int rc;

	if (no_overlay > 0) {
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		return -EINVAL;
	}

	rc = bttv_enum_fmt_cap_ovr(f);

	if (rc < 0)
		return rc;

	if (!(formats[rc].flags & FORMAT_FLAGS_PACKED))
		return -EINVAL;

	return 0;
}
