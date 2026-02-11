e_cal_util_construct_instance (icalcomponent *icalcomp,
                               struct icaltimetype rid)
{
	struct instance_data instance;
	struct icaltimetype start, end;

	g_return_val_if_fail (icalcomp != NULL, NULL);


	if (!icalcomponent_get_first_property (icalcomp, ICAL_RRULE_PROPERTY) &&
	    !icalcomponent_get_first_property (icalcomp, ICAL_RDATE_PROPERTY))
		return NULL;


	start = icaltime_convert_to_zone (rid, icaltimezone_get_utc_timezone ());
	end = start;
	icaltime_adjust (&end, 0, 0, 0, 1);

	instance.start = icaltime_as_timet (start);
	instance.found = FALSE;
	icalcomponent_foreach_recurrence (icalcomp, start, end,
					  check_instance, &instance);
	if (!instance.found)
		return NULL;


	icalcomp = icalcomponent_new_clone (icalcomp);
	icalcomponent_set_recurrenceid (icalcomp, rid);

	return icalcomp;
}
