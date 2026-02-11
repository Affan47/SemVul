GB_CanRaise(void *object, int event_id)
{
	ushort *event_tab;
	int func_id;
	COBSERVER *obs;

	if (!object || !OBJECT_has_events(object))
		return FALSE;

	LIST_for_each(obs, OBJECT_event(object)->observer)
	{
		if (OBJECT_active_parent(obs) && obs->event && obs->event[event_id])
			return TRUE;
	}

	if (!OBJECT_active_parent(object))
		return FALSE;

	event_tab = OBJECT_event(object)->event;
	func_id = event_tab[event_id];

	return (func_id != 0);
}
