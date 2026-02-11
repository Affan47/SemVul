icaltimezone_get_builtin_timezone_from_offset	(int offset, const char *tzname)
{
    icaltimezone *zone=NULL;
    int count, i;

    if (!builtin_timezones)
	icaltimezone_init_builtin_timezones ();

    if (offset==0)
	return &utc_timezone;

    if (!tzname)
	return NULL;

    count = builtin_timezones->num_elements;

    for (i=0; i<count; i++) {
	int z_offset;
	zone = icalarray_element_at (builtin_timezones, i);
	if (!zone->component)
	    icaltimezone_load_builtin_timezone (zone);

	z_offset = get_offset(zone);

	if (z_offset == offset && zone->tznames && !strcmp(tzname, zone->tznames))
	    return zone;
    }

    return NULL;
}
