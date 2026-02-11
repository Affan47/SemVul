emmaprp_queue_setup(struct vb2_queue *vq,
				const void *parg,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[], void *alloc_ctxs[])
{
	struct emmaprp_ctx *ctx = vb2_get_drv_priv(vq);
	struct emmaprp_q_data *q_data;
	unsigned int size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	if (q_data->fmt->fourcc == V4L2_PIX_FMT_YUV420)
		size = q_data->width * q_data->height * 3 / 2;
	else
		size = q_data->width * q_data->height * 2;

	while (size * count > MEM2MEM_VID_MEM_LIMIT)
		(count)--;

	*nplanes = 1;
	*nbuffers = count;
	sizes[0] = size;

	alloc_ctxs[0] = ctx->dev->alloc_ctx;

	dprintk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	return 0;
}
