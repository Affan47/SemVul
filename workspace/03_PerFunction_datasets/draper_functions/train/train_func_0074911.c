find_format(struct v4l2_format *f)
{
	struct vpe_fmt *fmt;
	unsigned int k;

	for (k = 0; k < ARRAY_SIZE(vpe_formats); k++) {
		fmt = &vpe_formats[k];
		if (fmt->fourcc == f->fmt.pix.pixelformat)
			return fmt;
	}

	return NULL;
}
