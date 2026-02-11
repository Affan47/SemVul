gdata_calendar_service_query_events_async (GDataCalendarService *self, GDataCalendarCalendar *calendar, GDataQuery *query, GCancellable *cancellable,
                                           GDataQueryProgressCallback progress_callback, gpointer progress_user_data,
                                           GDestroyNotify destroy_progress_user_data,
                                           GAsyncReadyCallback callback, gpointer user_data)
{
	const gchar *uri;

	g_return_if_fail (GDATA_IS_CALENDAR_SERVICE (self));
	g_return_if_fail (GDATA_IS_CALENDAR_CALENDAR (calendar));
	g_return_if_fail (query == NULL || GDATA_IS_QUERY (query));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
	g_return_if_fail (callback != NULL);


	if (gdata_authorizer_is_authorized_for_domain (gdata_service_get_authorizer (GDATA_SERVICE (self)),
	                                               get_calendar_authorization_domain ()) == FALSE) {
		GSimpleAsyncResult *result = g_simple_async_result_new (G_OBJECT (self), callback, user_data, gdata_service_query_async);
		g_simple_async_result_set_error (result, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_AUTHENTICATION_REQUIRED, "%s",
		                                 _("You must be authenticated to query your own calendars."));
		g_simple_async_result_complete_in_idle (result);
		g_object_unref (result);

		return;
	}


	uri = gdata_entry_get_content_uri (GDATA_ENTRY (calendar));
	if (uri == NULL) {

		GSimpleAsyncResult *result = g_simple_async_result_new (G_OBJECT (self), callback, user_data, gdata_service_query_async);
		g_simple_async_result_set_error (result, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_AUTHENTICATION_REQUIRED, "%s",
		                                 _("The calendar did not have a content URI."));
		g_simple_async_result_complete_in_idle (result);
		g_object_unref (result);

		return;
	}


	gdata_service_query_async (GDATA_SERVICE (self), get_calendar_authorization_domain (), uri, query, GDATA_TYPE_CALENDAR_EVENT, cancellable,
	                           progress_callback, progress_user_data, destroy_progress_user_data, callback, user_data);
}
