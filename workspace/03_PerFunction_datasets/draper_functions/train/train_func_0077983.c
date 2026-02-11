on_close1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();

	g_return_if_fail(doc != NULL);

	document_close(doc);
}
