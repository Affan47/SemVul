isns_flush_events(void)
{
	while (!isns_list_empty(&events)) {
		isns_cb_event_t *ev = isns_list_item(isns_cb_event_t, list, events.next);

		isns_call_callbacks(&ev->info);
		isns_object_release(ev->info.ie_recipient);
		isns_object_release(ev->info.ie_object);
		isns_object_release(ev->info.ie_trigger);
		isns_list_del(&ev->list);
		isns_free(ev);
	}
}
