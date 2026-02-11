init_event_waiter(struct kfd_process *p,
		struct kfd_event_waiter *waiter,
		uint32_t event_id,
		uint32_t input_index)
{
	struct kfd_event *ev = lookup_event_by_id(p, event_id);

	if (!ev)
		return -EINVAL;

	waiter->event = ev;
	waiter->input_index = input_index;
	waiter->activated = ev->signaled;
	ev->signaled = ev->signaled && !ev->auto_reset;

	list_add(&waiter->waiters, &ev->waiters);

	return 0;
}
