on_zoom_in1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();
	static gint done = 1;

	g_return_if_fail(doc != NULL);

	if (done++ % 3 == 0)
		sci_set_line_numbers(doc->editor->sci, editor_prefs.show_linenumber_margin,
				(sci_get_zoom(doc->editor->sci) / 2));
	sci_zoom_in(doc->editor->sci);
}
