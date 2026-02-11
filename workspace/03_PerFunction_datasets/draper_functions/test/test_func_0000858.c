soup_host_uri_equal (gconstpointer v1, gconstpointer v2)
{
	const SoupURI *one = v1;
	const SoupURI *two = v2;

	g_return_val_if_fail (one != NULL && two != NULL, one == two);
	g_return_val_if_fail (one->host != NULL && two->host != NULL, one->host == two->host);

	if (one->port != two->port)
		return FALSE;

	return g_ascii_strcasecmp (one->host, two->host) == 0;
}
