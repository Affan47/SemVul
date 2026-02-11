cx18_g_frequency(struct file *file, void *fh,
				struct v4l2_frequency *vf)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (vf->tuner != 0)
		return -EINVAL;

	cx18_call_all(cx, tuner, g_frequency, vf);
	return 0;
}
