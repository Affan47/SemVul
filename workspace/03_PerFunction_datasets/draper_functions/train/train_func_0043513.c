gth_catalog_set_order (GthCatalog *catalog,
		       const char *order,
		       gboolean    inverse)
{
	g_free (catalog->priv->order);
	catalog->priv->order = NULL;

	if (order != NULL)
		catalog->priv->order = g_strdup (order);
	catalog->priv->order_inverse = inverse;
}
