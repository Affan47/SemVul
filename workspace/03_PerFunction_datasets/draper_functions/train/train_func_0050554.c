prompt_password_perform (Test *test,
                         const gchar *prompt_path,
                         const gchar *password,
                         const GVariantType *type)
{
	GVariant *prompt_result = NULL;
	GError *error = NULL;
	GVariant *inside;
	GVariant *retval;
	guint sig;


	gcr_mock_prompter_expect_password_ok (password, NULL);


	sig = g_dbus_connection_signal_subscribe (test->service.connection,
	                                          test->service.bus_name,
	                                          SECRET_PROMPT_INTERFACE,
	                                          "Completed",
	                                          prompt_path,
	                                          NULL,
	                                          G_DBUS_SIGNAL_FLAGS_NONE,
	                                          on_prompt_completed,
	                                          &prompt_result,
	                                          NULL);


	retval = g_dbus_connection_call_sync (test->service.connection,
	                                      test->service.bus_name,
	                                      prompt_path,
	                                      SECRET_PROMPT_INTERFACE,
	                                      "Prompt",
	                                      g_variant_new ("(s)", ""),
	                                      G_VARIANT_TYPE ("()"),
	                                      G_DBUS_CALL_FLAGS_NONE,
	                                      -1, NULL, &error);
	g_assert_no_error (error);
	g_variant_unref (retval);

	egg_test_wait ();


	g_dbus_connection_signal_unsubscribe (test->service.connection, sig);
	g_assert (!gcr_mock_prompter_is_expecting ());


	g_assert (prompt_result != NULL);
	inside = g_variant_get_variant (prompt_result);
	g_assert (g_variant_is_of_type (inside, type));
	g_variant_unref (prompt_result);

	return inside;
}
