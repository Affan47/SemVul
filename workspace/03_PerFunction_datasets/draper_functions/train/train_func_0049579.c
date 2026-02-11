rb_set_back_events(time_t by)
{
	rb_dlink_node *ptr;
	struct ev_entry *ev;
	RB_DLINK_FOREACH(ptr, event_list.head)
	{
		ev = ptr->data;
		if(ev->when > by)
			ev->when -= by;
		else
			ev->when = 0;
	}
}
