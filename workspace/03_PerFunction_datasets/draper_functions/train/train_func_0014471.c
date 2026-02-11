soup_address_equal_by_ip (gconstpointer addr1, gconstpointer addr2)
{
	SoupAddressPrivate *priv1 = SOUP_ADDRESS_GET_PRIVATE (addr1);
	SoupAddressPrivate *priv2 = SOUP_ADDRESS_GET_PRIVATE (addr2);
	int size;

	g_return_val_if_fail (priv1->sockaddr != NULL, FALSE);
	g_return_val_if_fail (priv2->sockaddr != NULL, FALSE);

	size = SOUP_ADDRESS_FAMILY_SOCKADDR_SIZE (priv1->sockaddr->ss_family);
	return (priv1->sockaddr->ss_family ==
		priv2->sockaddr->ss_family &&
		!memcmp (priv1->sockaddr, priv2->sockaddr, size));
}
