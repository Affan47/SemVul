gdata_entry_look_up_links (GDataEntry *self, const gchar *rel)
{
	GList *i, *results = NULL;

	g_return_val_if_fail (GDATA_IS_ENTRY (self), NULL);
	g_return_val_if_fail (rel != NULL, NULL);

	for (i = self->priv->links; i != NULL; i = i->next) {
		const gchar *relation_type = gdata_link_get_relation_type (((GDataLink*) i->data));
		if (strcmp (relation_type, rel) == 0)
			results = g_list_prepend (results, i->data);
	}

	return g_list_reverse (results);
}
