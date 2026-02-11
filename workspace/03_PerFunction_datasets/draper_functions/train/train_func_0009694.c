meas_start(void)
{
	const struct frame *frame;
	struct vec *vec;

	n_samples = 0;
	for (frame = frames; frame; frame = frame->next)
		for (vec = frame->vecs; vec; vec = vec->next)
			vec->n = n_samples++;
}
