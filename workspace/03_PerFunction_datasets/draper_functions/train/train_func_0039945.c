ecal_test_utils_cal_add_timezone (ECal *cal,
                                  icaltimezone *zone)
{
	GError *error = NULL;
	const gchar *name;

	name = icaltimezone_get_display_name (zone);

	if (!e_cal_add_timezone (cal, zone, &error)) {
		g_warning ("failed to add icaltimezone '%s'; %s\n", name, error->message);
		exit (1);
	}
	test_print ("successfully added icaltimezone '%s'\n", name);
}
