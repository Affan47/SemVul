data_cal_complete_get_timezone_cb (GObject *source_object,
                                   GAsyncResult *result,
                                   gpointer user_data)
{
	AsyncContext *async_context = user_data;
	gchar *tzobject;
	GError *error = NULL;


	tzobject = e_cal_backend_get_timezone_finish (
		E_CAL_BACKEND (source_object), result, &error);


	g_return_if_fail (
		((tzobject != NULL) && (error == NULL)) ||
		((tzobject == NULL) && (error != NULL)));

	if (tzobject != NULL) {
		e_dbus_calendar_complete_get_timezone (
			async_context->interface,
			async_context->invocation,
			tzobject);

		g_free (tzobject);
	} else {
		data_cal_convert_to_client_error (error);
		g_dbus_method_invocation_take_error (
			async_context->invocation, error);
	}

	async_context_free (async_context);
}
