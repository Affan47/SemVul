on_settings_change(G_GNUC_UNUSED GObject *obj, G_GNUC_UNUSED GKeyFile *keyfile,
	G_GNUC_UNUSED gpointer gdata)
{
	update_home_key();

	if (column_mode)
	{
		guint i;

		foreach_document(i)
			assign_select_keys(documents[i]->editor->sci);
	}
}
