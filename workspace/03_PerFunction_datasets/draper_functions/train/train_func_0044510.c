hub_event_loop(struct hub_info* hub)
{
	do
	{
		net_backend_process();
		event_queue_process(hub->queue);
	}
	while (hub->status == hub_status_running || hub->status == hub_status_disabled);


	if (hub->status == hub_status_shutdown)
	{
		LOG_DEBUG("Removing all users...");
		event_queue_process(hub->queue);
		event_queue_process(hub->queue);
		hub_disconnect_all(hub);
		event_queue_process(hub->queue);
		hub->status = hub_status_stopped;
	}
}
