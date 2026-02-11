dbus_call_perform (Test *test,
                   const gchar *object_path,
                   const gchar *interface,
                   const gchar *member,
                   GVariant *parameters,
                   const GVariantType *restype,
                   GError **error)
{
	GAsyncResult *result = NULL;
	GVariant *retval;


	g_dbus_connection_call (test->service.connection,
	                        test->service.bus_name,
	                        object_path,
	                        interface,
	                        member,
	                        parameters,
	                        restype,
	                        G_DBUS_CALL_FLAGS_NO_AUTO_START,
	                        -1, NULL,
	                        on_complete_get_result,
	                        &result);

	g_assert (result == NULL);
	egg_test_wait ();
	g_assert (result != NULL);

	retval = g_dbus_connection_call_finish (test->service.connection,
	                                        result, error);
	g_object_unref (result);

	return retval;
}
