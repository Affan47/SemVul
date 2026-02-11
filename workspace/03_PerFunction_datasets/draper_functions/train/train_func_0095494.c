e_source_registry_authenticate_sync (ESourceRegistry *registry,
                                     ESource *source,
                                     ESourceAuthenticator *auth,
                                     GCancellable *cancellable,
                                     GError **error)
{
	AuthContext *auth_context;
	GMainContext *main_context;
	EDBusAuthenticator *dbus_auth;
	gboolean without_password;
	gchar *encryption_key;
	gchar *object_path = NULL;
	GError *local_error = NULL;

	g_return_val_if_fail (E_IS_SOURCE_REGISTRY (registry), FALSE);
	g_return_val_if_fail (E_IS_SOURCE (source), FALSE);
	g_return_val_if_fail (E_IS_SOURCE_AUTHENTICATOR (auth), FALSE);


	source_registry_call_authenticate_for_source (
		registry, auth, source, &object_path,
		cancellable, &local_error);

	if (local_error != NULL) {
		g_warn_if_fail (object_path == NULL);
		g_propagate_error (error, local_error);
		return FALSE;
	}

	g_return_val_if_fail (object_path != NULL, FALSE);

	main_context = g_main_context_new ();
	g_main_context_push_thread_default (main_context);

	dbus_auth = e_dbus_authenticator_proxy_new_for_bus_sync (
		G_BUS_TYPE_SESSION,
		G_DBUS_PROXY_FLAGS_NONE,
		SOURCES_DBUS_SERVICE_NAME,
		object_path, cancellable, &local_error);

	g_free (object_path);


	g_return_val_if_fail (
		((dbus_auth != NULL) && (local_error == NULL)) ||
		((dbus_auth == NULL) && (local_error != NULL)), FALSE);

	if (local_error != NULL)
		goto exit;

	without_password = e_source_authenticator_get_without_password (auth);
	e_dbus_authenticator_set_without_password (dbus_auth, without_password);

	auth_context = g_slice_new0 (AuthContext);
	auth_context->auth = g_object_ref (auth);
	auth_context->dbus_auth = dbus_auth;
	auth_context->main_loop = g_main_loop_new (main_context, FALSE);
	auth_context->error = &local_error;


	auth_context->auth_result = E_SOURCE_AUTHENTICATION_REJECTED;

	if (G_IS_CANCELLABLE (cancellable))
		auth_context->cancellable = g_object_ref (cancellable);

	auth_context->secret_exchange =
		gcr_secret_exchange_new (GCR_SECRET_EXCHANGE_PROTOCOL_1);

	g_signal_connect (
		dbus_auth, "authenticate",
		G_CALLBACK (source_registry_authenticate_authenticate_cb),
		auth_context);

	g_signal_connect (
		dbus_auth, "dismissed",
		G_CALLBACK (source_registry_authenticate_dismissed_cb),
		auth_context);

	g_signal_connect (
		dbus_auth, "server-error",
		G_CALLBACK (source_registry_authenticate_server_error_cb),
		auth_context);

	encryption_key = gcr_secret_exchange_begin (
		auth_context->secret_exchange);


	e_dbus_authenticator_call_ready_sync (
		dbus_auth, encryption_key, cancellable, &local_error);

	g_free (encryption_key);

	if (local_error == NULL)
		g_main_loop_run (auth_context->main_loop);

	auth_context_free (auth_context);

exit:
	g_main_context_pop_thread_default (main_context);


	while (g_main_context_pending (main_context))
		g_main_context_iteration (main_context, FALSE);

	g_main_context_unref (main_context);

	if (local_error != NULL) {
		g_dbus_error_strip_remote_error (local_error);
		g_propagate_error (error, local_error);
		return FALSE;
	}

	return TRUE;
}
