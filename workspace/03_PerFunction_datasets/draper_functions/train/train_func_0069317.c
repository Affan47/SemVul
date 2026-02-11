on_show_color_chooser1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	gchar colour[9];
	GeanyDocument *doc = document_get_current();
	gint pos;

	g_return_if_fail(doc != NULL);

	pos = sci_get_current_position(doc->editor->sci);
	editor_find_current_word(doc->editor, pos, colour, sizeof colour, GEANY_WORDCHARS"#");
	tools_color_chooser(colour);
}
