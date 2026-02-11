gdata_oauth2_authorizer_process_request (GDataAuthorizer *authorizer,
                                         GDataAuthorizationDomain *domain,
                                         SoupMessage *message)
{
	EGDataOAuth2AuthorizerPrivate *priv;
	gchar *authorization;

	priv = E_GDATA_OAUTH2_AUTHORIZER_GET_PRIVATE (authorizer);

	g_mutex_lock (&mutex);

	if (!gdata_oauth2_authorizer_is_authorized (authorizer, domain))
		goto exit;


	if (priv->access_token == NULL)
		goto exit;

	authorization = g_strdup_printf ("OAuth %s", priv->access_token);


	soup_message_headers_replace (
		message->request_headers,
		"Authorization", authorization);

	g_free (authorization);

exit:
	g_mutex_unlock (&mutex);
}
