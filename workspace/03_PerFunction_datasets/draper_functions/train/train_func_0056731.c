search_box_set_replace_string (SearchBox* search_box, const gchar* replace)
{
	g_return_if_fail (search_box != NULL && SEARCH_IS_BOX(search_box));

	gtk_entry_set_text (GTK_ENTRY (search_box->priv->replace_entry), replace);
}
