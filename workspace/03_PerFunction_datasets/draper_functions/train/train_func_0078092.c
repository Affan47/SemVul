soup_address_set_property (GObject *object, guint prop_id,
			   const GValue *value, GParamSpec *pspec)
{
	SoupAddressPrivate *priv = SOUP_ADDRESS_GET_PRIVATE (object);
	SoupAddressFamily family;
	struct sockaddr *sa;
	int len, port;


	switch (prop_id) {
	case PROP_NAME:
		priv->name = g_value_dup_string (value);
		break;

	case PROP_FAMILY:
		family = g_value_get_enum (value);
		if (family == SOUP_ADDRESS_FAMILY_INVALID)
			return;
		g_return_if_fail (SOUP_ADDRESS_FAMILY_IS_VALID (family));
		g_return_if_fail (priv->sockaddr == NULL);

		priv->sockaddr = g_malloc0 (SOUP_ADDRESS_FAMILY_SOCKADDR_SIZE (family));
		SOUP_ADDRESS_SET_FAMILY (priv, family);
		SOUP_ADDRESS_SET_PORT (priv, htons (priv->port));
		priv->n_addrs = 1;
		break;

	case PROP_PORT:
		port = g_value_get_int (value);
		if (port == -1)
			return;
		g_return_if_fail (SOUP_ADDRESS_PORT_IS_VALID (port));

		priv->port = port;
		if (priv->sockaddr)
			SOUP_ADDRESS_SET_PORT (priv, htons (port));
		break;

	case PROP_PROTOCOL:
		priv->protocol = g_intern_string (g_value_get_string (value));
		break;

	case PROP_SOCKADDR:
		sa = g_value_get_pointer (value);
		if (!sa)
			return;
		g_return_if_fail (priv->sockaddr == NULL);

		len = SOUP_ADDRESS_FAMILY_SOCKADDR_SIZE (sa->sa_family);
		priv->sockaddr = g_memdup (sa, len);
		priv->n_addrs = 1;
		priv->port = ntohs (SOUP_ADDRESS_GET_PORT (priv));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
