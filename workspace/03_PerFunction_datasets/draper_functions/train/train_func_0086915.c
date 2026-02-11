test_modify_object_sync (ETestServerFixture *fixture,
                         gconstpointer user_data)
{
	ECalClient *cal_client;
	GError *error = NULL;
	icalcomponent *icalcomp = NULL;
	const gchar *uid;

	cal_client = E_TEST_SERVER_UTILS_SERVICE (fixture, ECalClient);

	setup_cal (cal_client);
	uid = g_object_get_data (G_OBJECT (cal_client), "use-uid");
	g_assert (uid != NULL);

	if (!e_cal_client_get_object_sync (cal_client, uid, NULL, &icalcomp, NULL, &error))
		g_error ("get object sync: %s", error->message);

	icalcomponent_set_summary (icalcomp, EVENT_SUMMARY);

	if (!e_cal_client_modify_object_sync (cal_client, icalcomp, E_CAL_OBJ_MOD_ALL, NULL, &error))
		g_error ("modify object sync: %s", error->message);

	icalcomponent_free (icalcomp);

	if (!e_cal_client_get_object_sync (cal_client, uid, NULL, &icalcomp, NULL, &error))
		g_error ("get object sync after modification: %s", error->message);

	test_result (icalcomp);
	icalcomponent_free (icalcomp);
}
