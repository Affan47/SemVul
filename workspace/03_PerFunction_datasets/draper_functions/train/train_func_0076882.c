free_waiters(uint32_t num_events, struct kfd_event_waiter *waiters)
{
	uint32_t i;

	for (i = 0; i < num_events; i++)
		list_del(&waiters[i].waiters);

	kfree(waiters);
}
