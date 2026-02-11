tear_down_query_events (QueryEventsData *data, gconstpointer service)
{
	gdata_test_mock_server_start_trace (mock_server, "teardown-query-events");


	g_assert (gdata_service_delete_entry (GDATA_SERVICE (service), gdata_calendar_service_get_primary_authorization_domain (),
	                                      GDATA_ENTRY (data->event1), NULL, NULL) == TRUE);
	g_object_unref (data->event1);

	g_assert (gdata_service_delete_entry (GDATA_SERVICE (service), gdata_calendar_service_get_primary_authorization_domain (),
	                                      GDATA_ENTRY (data->event2), NULL, NULL) == TRUE);
	g_object_unref (data->event2);

	g_assert (gdata_service_delete_entry (GDATA_SERVICE (service), gdata_calendar_service_get_primary_authorization_domain (),
	                                      GDATA_ENTRY (data->event3), NULL, NULL) == TRUE);
	g_object_unref (data->event3);

	gdata_mock_server_end_trace (mock_server);


	tear_down_temp_calendar ((TempCalendarData*) data, service);
}
