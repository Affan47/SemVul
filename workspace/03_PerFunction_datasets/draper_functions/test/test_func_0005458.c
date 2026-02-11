camel_imapx_search_set_server (CamelIMAPXSearch *search,
                               CamelIMAPXServer *server)
{
	g_return_if_fail (CAMEL_IS_IMAPX_SEARCH (search));

	if (server != NULL)
		g_return_if_fail (CAMEL_IS_IMAPX_SERVER (server));

	g_weak_ref_set (&search->priv->server, server);

	g_object_notify (G_OBJECT (search), "server");
}
