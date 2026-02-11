mx2_videobuf_setup(struct vb2_queue *vq,
			const void *parg,
			unsigned int *count, unsigned int *num_planes,
			unsigned int sizes[], void *alloc_ctxs[])
{
	const struct v4l2_format *fmt = parg;
	struct soc_camera_device *icd = soc_camera_from_vb2q(vq);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct mx2_camera_dev *pcdev = ici->priv;

	dev_dbg(icd->parent, "count=%d, size=%d\n", *count, sizes[0]);


	if (fmt != NULL)
		return -ENOTTY;

	alloc_ctxs[0] = pcdev->alloc_ctx;

	sizes[0] = icd->sizeimage;

	if (0 == *count)
		*count = 32;
	if (!*num_planes &&
	    sizes[0] * *count > MAX_VIDEO_MEM * 1024 * 1024)
		*count = (MAX_VIDEO_MEM * 1024 * 1024) / sizes[0];

	*num_planes = 1;

	return 0;
}
