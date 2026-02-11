vmbus_setevent(struct vmbus_channel *channel)
{
	struct hv_monitor_page *monitorpage;


	if ((channel->offermsg.monitor_allocated) &&
	    (!channel->low_latency)) {

		sync_set_bit(channel->offermsg.child_relid & 31,
			(unsigned long *) vmbus_connection.send_int_page +
			(channel->offermsg.child_relid >> 5));


		monitorpage = vmbus_connection.monitor_pages[1];

		sync_set_bit(channel->monitor_bit,
			(unsigned long *)&monitorpage->trigger_group
					[channel->monitor_grp].pending);

	} else {
		vmbus_set_event(channel);
	}
}
