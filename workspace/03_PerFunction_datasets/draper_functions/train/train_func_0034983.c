tgt_add_sched_event(struct event_data *evt)
{
	if (!evt->scheduled) {
		evt->scheduled = 1;
		list_add_tail(&evt->e_list, &tgt_sched_events_list);
	}
}
