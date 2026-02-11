on_filetype_change(GtkCheckMenuItem *menuitem, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();
	if (ignore_callback || doc == NULL || ! gtk_check_menu_item_get_active(menuitem))
		return;

	document_set_filetype(doc, (GeanyFiletype*)user_data);
}
