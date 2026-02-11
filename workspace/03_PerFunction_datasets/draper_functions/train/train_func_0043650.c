print_events(void)
{
	list_node_t *it;
	for (it = events->head; it; it = it->next) {
		struct event *event = it->data;
		if (event)
			print_event(event);
	}
}
