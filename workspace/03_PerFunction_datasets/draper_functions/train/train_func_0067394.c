on_set_file_readonly1_toggled(GtkCheckMenuItem *checkmenuitem, gpointer user_data)
{
	if (! ignore_callback)
	{
		GeanyDocument *doc = document_get_current();
		g_return_if_fail(doc != NULL);

		doc->readonly = ! doc->readonly;
		sci_set_readonly(doc->editor->sci, doc->readonly);
		ui_update_tab_status(doc);
		ui_update_statusbar(doc, -1);
	}
}
