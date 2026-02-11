soup_auth_domain_digest_set_auth_callback (SoupAuthDomain *domain,
					   SoupAuthDomainDigestAuthCallback callback,
					   gpointer        user_data,
					   GDestroyNotify  dnotify)
{
	SoupAuthDomainDigestPrivate *priv =
		SOUP_AUTH_DOMAIN_DIGEST_GET_PRIVATE (domain);

	if (priv->auth_dnotify)
		priv->auth_dnotify (priv->auth_data);

	priv->auth_callback = callback;
	priv->auth_data = user_data;
	priv->auth_dnotify = dnotify;

	g_object_notify (G_OBJECT (domain), SOUP_AUTH_DOMAIN_DIGEST_AUTH_CALLBACK);
	g_object_notify (G_OBJECT (domain), SOUP_AUTH_DOMAIN_DIGEST_AUTH_DATA);
}
