test_remove_object_sync (ETestServerFixture *fixture,
                         gconstpointer user_data)
{
	ECalClient *cal_client;
	GError *error = NULL;
	gchar *uid;

	cal_client = E_TEST_SERVER_UTILS_SERVICE (fixture, ECalClient);

	uid = create_object (cal_client);
	g_assert (uid != NULL);

	if (!e_cal_client_remove_object_sync (cal_client, uid, NULL, E_CAL_OBJ_MOD_ALL, NULL, &error))
		g_error ("remove object sync: %s", error->message);

	g_free (uid);
}
