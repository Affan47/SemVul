proxy_settings_changed (EProxy *proxy,
                        gpointer user_data)
{
	SoupURI *proxy_uri = NULL;
	EEwsConnection *cnc = (EEwsConnection *) user_data;

	if (!cnc || !cnc->priv || !cnc->priv->uri || !cnc->priv->soup_session)
		return;


	if (e_proxy_require_proxy_for_uri (proxy, cnc->priv->uri)) {
		proxy_uri = e_proxy_peek_uri_for (proxy, cnc->priv->uri);
	}

	g_object_set (cnc->priv->soup_session, SOUP_SESSION_PROXY_URI, proxy_uri, NULL);
}
