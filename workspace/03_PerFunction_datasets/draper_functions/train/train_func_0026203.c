event_delete(espeak_EVENT* event)
{
ENTER("event_delete");

	event_display(event);

	if(event==NULL)
	{
		return 0;
	}

	switch(event->type)
	{
	case espeakEVENT_MSG_TERMINATED:
		event_notify(event);
		break;

	case espeakEVENT_MARK:
	case espeakEVENT_PLAY:
		if(event->id.name)
		{
			free((void*)(event->id.name));
		}
		break;

	default:
		break;
	}

	free(event);
	return 1;
}
