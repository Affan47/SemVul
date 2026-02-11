parse_authentication_response (GDataClientLoginAuthorizer *self, GDataAuthorizationDomain *domain, guint status,
                               const gchar *response_body, gint length, GError **error)
{
	gchar *auth_start, *auth_end;
	GDataSecureString auth_token;


	auth_start = strstr (response_body, "Auth=");
	if (auth_start == NULL) {
		goto protocol_error;
	}
	auth_start += strlen ("Auth=");

	auth_end = strstr (auth_start, "\n");
	if (auth_end == NULL) {
		goto protocol_error;
	}

	auth_token = _gdata_service_secure_strndup (auth_start, auth_end - auth_start);
	if (auth_token == NULL || strlen (auth_token) == 0) {
		_gdata_service_secure_strfree (auth_token);
		goto protocol_error;
	}

	return auth_token;

protocol_error:
	g_set_error_literal (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,
	                     _("The server returned a malformed response."));
	return NULL;
}
