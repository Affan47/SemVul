setup_cal (ECalClient *cal_client)
{
	GError *error = NULL;
	icalcomponent *icalcomp;
	struct icaltimetype now;
	gchar *uid = NULL;

	now = icaltime_current_time_with_zone (icaltimezone_get_utc_timezone ());
	icalcomp = icalcomponent_new (ICAL_VEVENT_COMPONENT);
	icalcomponent_set_summary (icalcomp, "Test event summary");
	icalcomponent_set_dtstart (icalcomp, now);
	icalcomponent_set_dtend   (icalcomp, icaltime_from_timet (icaltime_as_timet (now) + 60 * 60 * 60, 0));

	if (!e_cal_client_create_object_sync (cal_client, icalcomp, &uid, NULL, &error))
		g_error ("create object sync: %s", error->message);

	icalcomponent_free (icalcomp);
	g_free (uid);
}
