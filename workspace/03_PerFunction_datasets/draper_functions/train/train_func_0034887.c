on_normal_size1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();

	g_return_if_fail(doc != NULL);

	sci_zoom_off(doc->editor->sci);
	sci_set_line_numbers(doc->editor->sci, editor_prefs.show_linenumber_margin, 0);
}
