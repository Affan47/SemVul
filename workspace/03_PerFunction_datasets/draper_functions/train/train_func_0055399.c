queue_setup(struct vb2_queue *q, const void *parg,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], void *alloc_ctxs[])
{
	struct cx23885_dev *dev = q->drv_priv;
	unsigned lines = VBI_PAL_LINE_COUNT;

	if (dev->tvnorm & V4L2_STD_525_60)
		lines = VBI_NTSC_LINE_COUNT;
	*num_planes = 1;
	sizes[0] = lines * VBI_LINE_LENGTH * 2;
	alloc_ctxs[0] = dev->alloc_ctx;
	return 0;
}
