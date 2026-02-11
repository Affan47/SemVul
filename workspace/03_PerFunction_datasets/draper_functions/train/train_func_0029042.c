gdata_entry_add_author (GDataEntry *self, GDataAuthor *author)
{

	g_return_if_fail (GDATA_IS_ENTRY (self));
	g_return_if_fail (GDATA_IS_AUTHOR (author));

	if (g_list_find_custom (self->priv->authors, author, (GCompareFunc) gdata_comparable_compare) == NULL)
		self->priv->authors = g_list_prepend (self->priv->authors, g_object_ref (author));
}
