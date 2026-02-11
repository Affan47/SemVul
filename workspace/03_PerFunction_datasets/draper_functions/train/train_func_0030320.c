dt3155_s_std(struct file *filp, void *p, v4l2_std_id norm)
{
	struct dt3155_priv *pd = video_drvdata(filp);

	if (pd->std == norm)
		return 0;
	if (vb2_is_busy(&pd->vidq))
		return -EBUSY;
	pd->std = norm;
	if (pd->std & V4L2_STD_525_60) {
		pd->csr2 = VT_60HZ;
		pd->width = 640;
		pd->height = 480;
	} else {
		pd->csr2 = VT_50HZ;
		pd->width = 768;
		pd->height = 576;
	}
	return 0;
}
