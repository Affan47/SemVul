gal_view_check_string (GalViewCollection *collection,
                       gchar *string)
{
	gint i;

	if (!strcmp (string, "current_view"))
		return FALSE;

	for (i = 0; i < collection->priv->view_count; i++) {
		if (!strcmp (string, collection->priv->view_data[i]->id))
			return FALSE;
	}
	for (i = 0; i < collection->priv->removed_view_count; i++) {
		if (!strcmp (string, collection->priv->removed_view_data[i]->id))
			return FALSE;
	}
	return TRUE;
}
