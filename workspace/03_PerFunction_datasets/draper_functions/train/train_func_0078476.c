bttv_enum_fmt_vid_cap(struct file *file, void  *priv,
				struct v4l2_fmtdesc *f)
{
	int rc = bttv_enum_fmt_cap_ovr(f);

	if (rc < 0)
		return rc;

	return 0;
}
