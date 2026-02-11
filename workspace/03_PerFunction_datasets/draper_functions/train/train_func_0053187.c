context_get_descriptors(struct context *ctx,
						  int z, dma_addr_t *d_bus)
{
	struct descriptor *d = NULL;
	struct descriptor_buffer *desc = ctx->buffer_tail;

	if (z * sizeof(*d) > desc->buffer_size)
		return NULL;

	if (z * sizeof(*d) > desc->buffer_size - desc->used) {


		if (desc->list.next == &ctx->buffer_list) {


			if (context_add_buffer(ctx) < 0)
				return NULL;
		}
		desc = list_entry(desc->list.next,
				struct descriptor_buffer, list);
		ctx->buffer_tail = desc;
	}

	d = desc->buffer + desc->used / sizeof(*d);
	memset(d, 0, z * sizeof(*d));
	*d_bus = desc->buffer_bus + desc->used;

	return d;
}
