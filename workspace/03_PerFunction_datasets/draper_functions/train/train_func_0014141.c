trace_create_new_event(struct trace_event_call *call,
		       struct trace_array *tr)
{
	struct trace_event_file *file;

	file = kmem_cache_alloc(file_cachep, GFP_TRACE);
	if (!file)
		return NULL;

	file->event_call = call;
	file->tr = tr;
	atomic_set(&file->sm_ref, 0);
	atomic_set(&file->tm_ref, 0);
	INIT_LIST_HEAD(&file->triggers);
	list_add(&file->list, &tr->events);

	return file;
}
