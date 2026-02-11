perf_aux_output_end(struct perf_output_handle *handle, unsigned long size,
			 bool truncated)
{
	struct ring_buffer *rb = handle->rb;
	bool wakeup = truncated;
	unsigned long aux_head;
	u64 flags = 0;

	if (truncated)
		flags |= PERF_AUX_FLAG_TRUNCATED;


	if (rb->aux_overwrite) {
		flags |= PERF_AUX_FLAG_OVERWRITE;

		aux_head = handle->head;
		local_set(&rb->aux_head, aux_head);
	} else {
		aux_head = local_read(&rb->aux_head);
		local_add(size, &rb->aux_head);
	}

	if (size || flags) {


		perf_event_aux_event(handle->event, aux_head, size, flags);
	}

	aux_head = rb->user_page->aux_head = local_read(&rb->aux_head);

	if (aux_head - local_read(&rb->aux_wakeup) >= rb->aux_watermark) {
		wakeup = true;
		local_add(rb->aux_watermark, &rb->aux_wakeup);
	}

	if (wakeup) {
		if (truncated)
			handle->event->pending_disable = 1;
		perf_output_wakeup(handle);
	}

	handle->event = NULL;

	local_set(&rb->aux_nest, 0);
	rb_free_aux(rb);
	ring_buffer_put_async(rb);
}
