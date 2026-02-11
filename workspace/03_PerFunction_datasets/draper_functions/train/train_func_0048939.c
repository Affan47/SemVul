dispose (GObject *object)
{
	NMDHCPClient *self = NM_DHCP_CLIENT (object);
	NMDHCPClientPrivate *priv = NM_DHCP_CLIENT_GET_PRIVATE (self);


	if (priv->remove_id)
		g_source_remove (priv->remove_id);

	g_hash_table_destroy (priv->options);
	g_free (priv->iface);
	if (priv->hwaddr)
		g_byte_array_free (priv->hwaddr, TRUE);

	if (priv->duid)
		g_byte_array_free (priv->duid, TRUE);

	G_OBJECT_CLASS (nm_dhcp_client_parent_class)->dispose (object);
}
