freerdp_event_new(uint32 event_type, FRDP_EVENT_CALLBACK on_event_free_callback, void* user_data)
{
	FRDP_EVENT* event = NULL;

	switch (event_type)
	{
		case FRDP_EVENT_TYPE_DEBUG:
			event = xnew(FRDP_EVENT);
			break;
		case FRDP_EVENT_TYPE_VIDEO_FRAME:
			event = (FRDP_EVENT*)xnew(FRDP_VIDEO_FRAME_EVENT);
			break;
		case FRDP_EVENT_TYPE_REDRAW:
			event = (FRDP_EVENT*)xnew(FRDP_REDRAW_EVENT);
			break;
		case FRDP_EVENT_TYPE_CB_SYNC:
			event = (FRDP_EVENT*)xnew(FRDP_CB_SYNC_EVENT);
			break;
		case FRDP_EVENT_TYPE_CB_FORMAT_LIST:
			event = (FRDP_EVENT*)xnew(FRDP_CB_FORMAT_LIST_EVENT);
			break;
		case FRDP_EVENT_TYPE_CB_DATA_REQUEST:
			event = (FRDP_EVENT*)xnew(FRDP_CB_DATA_REQUEST_EVENT);
			break;
		case FRDP_EVENT_TYPE_CB_DATA_RESPONSE:
			event = (FRDP_EVENT*)xnew(FRDP_CB_DATA_RESPONSE_EVENT);
			break;

		case FRDP_EVENT_TYPE_RAIL_UI_2_VCHANNEL:
		case FRDP_EVENT_TYPE_RAIL_VCHANNEL_2_UI:
			event = xnew(FRDP_EVENT);
			break;

	}
	if (event != NULL)
	{
		event->event_type = event_type;
		event->on_event_free_callback = on_event_free_callback;
		event->user_data = user_data;
	}

	return event;
}
