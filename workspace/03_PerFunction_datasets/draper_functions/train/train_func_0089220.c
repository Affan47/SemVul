session_authenticate_sync (CamelSession *session,
                           CamelService *service,
                           const gchar *mechanism,
                           GCancellable *cancellable,
                           GError **error)
{
	CamelServiceAuthType *authtype = NULL;
	CamelAuthenticationResult result;
	GError *local_error = NULL;


	g_warning (
		"The default CamelSession.authenticate_sync() "
		"method is not intended for production use.");


	if (mechanism != NULL) {
		authtype = camel_sasl_authtype (mechanism);
		if (authtype == NULL) {
			g_set_error (
				error, CAMEL_SERVICE_ERROR,
				CAMEL_SERVICE_ERROR_CANT_AUTHENTICATE,
				_("No support for %s authentication"),
				mechanism);
			return FALSE;
		}
	}


	if (authtype != NULL && !authtype->need_password) {
		result = camel_service_authenticate_sync (
			service, mechanism, cancellable, error);
		if (result == CAMEL_AUTHENTICATION_REJECTED)
			g_set_error (
				error, CAMEL_SERVICE_ERROR,
				CAMEL_SERVICE_ERROR_CANT_AUTHENTICATE,
				_("%s authentication failed"), mechanism);
		return (result == CAMEL_AUTHENTICATION_ACCEPTED);
	}


	if (mechanism != NULL) {
		CamelProvider *provider;
		CamelSasl *sasl;
		const gchar *service_name;
		gboolean success = FALSE;

		provider = camel_service_get_provider (service);
		service_name = provider->protocol;


		sasl = camel_sasl_new (service_name, mechanism, service);
		if (sasl != NULL) {
			success = camel_sasl_try_empty_password_sync (
				sasl, cancellable, &local_error);
			g_object_unref (sasl);
		}

		if (success)
			return TRUE;
	}


	if (g_error_matches (local_error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
		return FALSE;

	g_clear_error (&local_error);

retry:


	result = camel_service_authenticate_sync (
		service, mechanism, cancellable, error);

	if (result == CAMEL_AUTHENTICATION_REJECTED) {

		goto retry;
	}

	if (result == CAMEL_AUTHENTICATION_ACCEPTED) {


	}

	return (result == CAMEL_AUTHENTICATION_ACCEPTED);
}
