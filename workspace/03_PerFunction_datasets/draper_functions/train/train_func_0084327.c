soup_address_get_physical (SoupAddress *addr)
{
	SoupAddressPrivate *priv;

	g_return_val_if_fail (SOUP_IS_ADDRESS (addr), NULL);
	priv = SOUP_ADDRESS_GET_PRIVATE (addr);

	if (!priv->sockaddr)
		return NULL;

	if (!priv->physical) {
		GInetAddress *gia;

		gia = soup_address_make_inet_address (addr);
		priv->physical = g_inet_address_to_string (gia);
		g_object_unref (gia);
	}

	return priv->physical;
}
