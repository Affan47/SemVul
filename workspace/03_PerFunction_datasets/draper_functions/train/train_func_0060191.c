go7007_queue_setup(struct vb2_queue *q,
		const void *parg,
		unsigned int *num_buffers, unsigned int *num_planes,
		unsigned int sizes[], void *alloc_ctxs[])
{
	sizes[0] = GO7007_BUF_SIZE;
	*num_planes = 1;

	if (*num_buffers < 2)
		*num_buffers = 2;

	return 0;
}
