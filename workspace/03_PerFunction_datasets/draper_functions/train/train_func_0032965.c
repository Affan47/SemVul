alloc_event_waiters(uint32_t num_events)
{
	struct kfd_event_waiter *event_waiters;
	uint32_t i;

	event_waiters = kmalloc_array(num_events,
					sizeof(struct kfd_event_waiter),
					GFP_KERNEL);

	for (i = 0; (event_waiters) && (i < num_events) ; i++) {
		INIT_LIST_HEAD(&event_waiters[i].waiters);
		event_waiters[i].sleeping_task = current;
		event_waiters[i].activated = false;
	}

	return event_waiters;
}
