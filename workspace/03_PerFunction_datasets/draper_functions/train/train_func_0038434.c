soup_proxy_resolver_default_constructed (GObject *object)
{
	SoupProxyResolverDefaultPrivate *priv = SOUP_PROXY_RESOLVER_DEFAULT_GET_PRIVATE (object);

	if (!priv->gproxy_resolver) {
		priv->gproxy_resolver = g_proxy_resolver_get_default ();
		g_object_ref (priv->gproxy_resolver);
	}

	G_OBJECT_CLASS (soup_proxy_resolver_default_parent_class)->constructed (object);
}
