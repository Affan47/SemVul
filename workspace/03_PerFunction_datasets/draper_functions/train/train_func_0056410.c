soup_session_prepare_for_uri (SoupSession *session, SoupURI *uri)
{
	g_return_if_fail (SOUP_IS_SESSION (session));
	g_return_if_fail (uri != NULL);

	if (!uri->host)
		return;

	prefetch_uri (session, uri, NULL, NULL, NULL);
}
