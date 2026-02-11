ev_getevent(event_t *ev)
{
	if (eventpos == eventhead)
	{
		ev->type = EV_NONE;
		return 0;
	}
	*ev = eventqueue[eventpos];
	eventpos = (eventpos+1)%MAX_EVENTS;
	if (ev->type == EV_PRESS)
	{
		keystates[ev->code] = 1;
		nkeysdown++;
	}
	if (ev->type == EV_RELEASE)
	{
		keystates[ev->code] = 0;
		nkeysdown--;
		if (nkeysdown < 0) nkeysdown = 0;
	}
	return 1;
}
