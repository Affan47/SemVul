event_queue_initialize(struct event_queue** queue, event_queue_callback callback, void* ptr)
{
	*queue = (struct event_queue*) hub_malloc_zero(sizeof(struct event_queue));
	if (!(*queue))
		return -1;

	(*queue)->q1 = list_create();
	(*queue)->q2 = list_create();

	if (!(*queue)->q1 || !(*queue)->q2)
	{
		list_destroy((*queue)->q1);
		list_destroy((*queue)->q2);
		return -1;
	}

	(*queue)->callback = callback;
	(*queue)->callback_data = ptr;

	return 0;
}
