ev_postevent(event_t *ev)
{
	int nextevent;
	nextevent = (eventhead+1)%MAX_EVENTS;
	if (nextevent == eventpos)
		return 0;
	eventqueue[eventhead] = *ev;
	eventhead = nextevent;
	return 1;
}
