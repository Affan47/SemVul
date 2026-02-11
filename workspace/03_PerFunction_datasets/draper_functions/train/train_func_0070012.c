sink_down(heap_context ctx, int i, void *elt) {
	int j, size, half_size;

	size = ctx->heap_size;
	half_size = size / 2;
	while (i <= half_size) {

		j = heap_left(i);
		if (j < size && ctx->higher_priority(ctx->heap[j+1],
						     ctx->heap[j]))
			j++;
		if (ctx->higher_priority(elt, ctx->heap[j]))
			break;
		ctx->heap[i] = ctx->heap[j];
		if (ctx->index != NULL)
			(ctx->index)(ctx->heap[i], i);
		i = j;
	}
	ctx->heap[i] = elt;
	if (ctx->index != NULL)
		(ctx->index)(ctx->heap[i], i);
}
