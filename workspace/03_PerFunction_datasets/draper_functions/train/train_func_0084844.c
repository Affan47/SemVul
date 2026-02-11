signon_session_password_process_cb (GObject *source_object,
                                    GAsyncResult *result,
                                    gpointer user_data)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;
	GVariant *session_data;
	GVariant *secret;
	GString *string = NULL;
	GError *error = NULL;

	simple = G_SIMPLE_ASYNC_RESULT (user_data);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	session_data = signon_auth_session_process_finish (
		SIGNON_AUTH_SESSION (source_object), result, &error);


	g_return_if_fail (
		((session_data != NULL) && (error == NULL)) ||
		((session_data == NULL) && (error != NULL)));

	if (error != NULL) {
		g_simple_async_result_take_error (simple, error);
		g_simple_async_result_complete (simple);
		goto exit;
	}

	secret = g_variant_lookup_value (
		session_data,
		SIGNON_SESSION_DATA_SECRET,
		G_VARIANT_TYPE_STRING);

	g_variant_unref (session_data);

	if (secret == NULL) {
		g_simple_async_result_set_error (
			simple, SIGNON_ERROR,
			SIGNON_ERROR_MISSING_DATA,
			_("Signon service did not return a secret"));
		g_simple_async_result_complete (simple);
		goto exit;
	}


	string = g_string_new (g_variant_get_string (secret, NULL));

	e_source_authenticator_try_password (
		async_context->authenticator,
		string,
		async_context->cancellable,
		signon_session_password_try_password_cb,
		g_object_ref (simple));

	g_string_free (string, TRUE);
	g_variant_unref (secret);

exit:
	g_object_unref (simple);
}
