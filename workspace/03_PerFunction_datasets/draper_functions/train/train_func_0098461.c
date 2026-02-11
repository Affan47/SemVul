test_get_object_list (ETestServerFixture *fixture,
                      gconstpointer user_data)
{
	ECal *cal;
	ECalComponent *e_component;
	icalcomponent *component;
	icalcomponent *component_final;
	gchar *uid;
	GList *components;

	cal = E_TEST_SERVER_UTILS_SERVICE (fixture, ECal);

	ecal_test_utils_create_component (
		cal,
		"20040109T090000Z", "UTC",
		"20040109T103000", "UTC",
		EVENT_SUMMARY, &e_component, &uid);
	component = e_cal_component_get_icalcomponent (e_component);

	component_final = ecal_test_utils_cal_get_object (cal, uid);
	ecal_test_utils_cal_assert_objects_equal_shallow (
		component,
			component_final);
	icalcomponent_free (component_final);

	components = ecal_test_utils_cal_get_object_list (
		cal, "(contains? \"summary\" \"" EVENT_SUMMARY "\")");
	g_assert (g_list_length (components) == 1);
	component_final = components->data;
	ecal_test_utils_cal_assert_objects_equal_shallow (
		component, component_final);

	e_cal_free_object_list (components);
	g_free (uid);
	icalcomponent_free (component);
}
