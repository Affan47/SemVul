_gdata_query_set_previous_uri (GDataQuery *self, const gchar *previous_uri)
{
	g_return_if_fail (GDATA_IS_QUERY (self));
	g_free (self->priv->previous_uri);
	self->priv->previous_uri = g_strdup (previous_uri);
	self->priv->use_next_uri = FALSE;
	self->priv->use_previous_uri = FALSE;
}
