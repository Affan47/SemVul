analog_get_callerid(struct analog_pvt *p, char *name, char *number, enum analog_event *ev, size_t timeout)
{
	if (analog_callbacks.get_callerid) {
		return analog_callbacks.get_callerid(p->chan_pvt, name, number, ev, timeout);
	}
	return -1;
}
