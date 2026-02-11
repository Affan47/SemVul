cx18_g_sliced_vbi_cap(struct file *file, void *fh,
					struct v4l2_sliced_vbi_cap *cap)
{
	struct cx18 *cx = fh2id(fh)->cx;
	int set = cx->is_50hz ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525;
	int f, l;

	if (cap->type != V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
		return -EINVAL;

	cap->service_set = 0;
	for (f = 0; f < 2; f++) {
		for (l = 0; l < 24; l++) {
			if (valid_service_line(f, l, cx->is_50hz)) {


				cap->service_lines[f][l] = set;
				cap->service_set |= set;
			} else
				cap->service_lines[f][l] = 0;
		}
	}
	for (f = 0; f < 3; f++)
		cap->reserved[f] = 0;
	return 0;
}
