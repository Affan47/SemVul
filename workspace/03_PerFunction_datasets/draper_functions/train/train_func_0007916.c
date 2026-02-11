toggle_dsTrace(struct toggle *t _is_unused, enum toggle_type tt)
{

	if (toggled(DS_TRACE) && tracef == NULL)
		tracefile_on(DS_TRACE, tt);


	else if (!toggled(DS_TRACE) && !toggled(EVENT_TRACE))
		tracefile_off();

	if (toggled(DS_TRACE))
		(void) gettimeofday(&ds_ts, (struct timezone *)NULL);
}
