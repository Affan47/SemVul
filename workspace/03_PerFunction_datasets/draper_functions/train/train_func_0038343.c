brasero_data_project_exclude_uri (BraseroDataProject *self,
				  const gchar *uri)
{
	BraseroDataProjectPrivate *priv;

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);


	if (!g_hash_table_lookup (priv->grafts, uri)) {

		brasero_data_project_uri_add_graft (self, uri);
	}
}
