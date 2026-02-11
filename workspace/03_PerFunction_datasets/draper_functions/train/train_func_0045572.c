vid_out_queue_setup(struct vb2_queue *vq, const void *parg,
		       unsigned *nbuffers, unsigned *nplanes,
		       unsigned sizes[], void *alloc_ctxs[])
{
	const struct v4l2_format *fmt = parg;
	struct vivid_dev *dev = vb2_get_drv_priv(vq);
	const struct vivid_fmt *vfmt = dev->fmt_out;
	unsigned planes = vfmt->buffers;
	unsigned h = dev->fmt_out_rect.height;
	unsigned size = dev->bytesperline_out[0] * h;
	unsigned p;

	for (p = vfmt->buffers; p < vfmt->planes; p++)
		size += dev->bytesperline_out[p] * h / vfmt->vdownsampling[p];

	if (dev->field_out == V4L2_FIELD_ALTERNATE) {


		if (vb2_fileio_is_active(vq))
			return -EINVAL;
	}

	if (dev->queue_setup_error) {


		dev->queue_setup_error = false;
		return -EINVAL;
	}

	if (fmt) {
		const struct v4l2_pix_format_mplane *mp;
		struct v4l2_format mp_fmt;

		if (!V4L2_TYPE_IS_MULTIPLANAR(fmt->type)) {
			fmt_sp2mp(fmt, &mp_fmt);
			fmt = &mp_fmt;
		}
		mp = &fmt->fmt.pix_mp;


		if (mp->num_planes != planes)
			return -EINVAL;
		sizes[0] = mp->plane_fmt[0].sizeimage;
		if (sizes[0] < size)
			return -EINVAL;
		for (p = 1; p < planes; p++) {
			sizes[p] = mp->plane_fmt[p].sizeimage;
			if (sizes[p] < dev->bytesperline_out[p] * h)
				return -EINVAL;
		}
	} else {
		for (p = 0; p < planes; p++)
			sizes[p] = p ? dev->bytesperline_out[p] * h : size;
	}

	if (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = planes;


	dprintk(dev, 1, "%s: count=%d\n", __func__, *nbuffers);
	for (p = 0; p < planes; p++)
		dprintk(dev, 1, "%s: size[%u]=%u\n", __func__, p, sizes[p]);
	return 0;
}
