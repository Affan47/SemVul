get_provider_info (GcIfaceGeoclue *geoclue,
		   gchar          **name,
		   gchar          **description,
		   GError        **error)
{
	GcProvider *provider = GC_PROVIDER (geoclue);
	GcProviderPrivate *priv = GET_PRIVATE (provider);

	if (name) {
		*name = g_strdup (priv->name);
	}
	if (description) {
		*description = g_strdup (priv->description);
	}

	return TRUE;
}
