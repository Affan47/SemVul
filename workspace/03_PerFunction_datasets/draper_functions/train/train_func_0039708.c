binder_delete_free_buffer(struct binder_proc *proc,
				      struct binder_buffer *buffer)
{
	struct binder_buffer *prev, *next = NULL;
	int free_page_end = 1;
	int free_page_start = 1;

	BUG_ON(proc->buffers.next == &buffer->entry);
	prev = list_entry(buffer->entry.prev, struct binder_buffer, entry);
	BUG_ON(!prev->free);
	if (buffer_end_page(prev) == buffer_start_page(buffer)) {
		free_page_start = 0;
		if (buffer_end_page(prev) == buffer_end_page(buffer))
			free_page_end = 0;
		binder_debug(BINDER_DEBUG_BUFFER_ALLOC,
			     "%d: merge free, buffer %p share page with %p\n",
			      proc->pid, buffer, prev);
	}

	if (!list_is_last(&buffer->entry, &proc->buffers)) {
		next = list_entry(buffer->entry.next,
				  struct binder_buffer, entry);
		if (buffer_start_page(next) == buffer_end_page(buffer)) {
			free_page_end = 0;
			if (buffer_start_page(next) ==
			    buffer_start_page(buffer))
				free_page_start = 0;
			binder_debug(BINDER_DEBUG_BUFFER_ALLOC,
				     "%d: merge free, buffer %p share page with %p\n",
				      proc->pid, buffer, prev);
		}
	}
	list_del(&buffer->entry);
	if (free_page_start || free_page_end) {
		binder_debug(BINDER_DEBUG_BUFFER_ALLOC,
			     "%d: merge free, buffer %p do not share page%s%s with %p or %p\n",
			     proc->pid, buffer, free_page_start ? "" : " end",
			     free_page_end ? "" : " start", prev, next);
		binder_update_page_range(proc, 0, free_page_start ?
			buffer_start_page(buffer) : buffer_end_page(buffer),
			(free_page_end ? buffer_end_page(buffer) :
			buffer_start_page(buffer)) + PAGE_SIZE, NULL);
	}
}
