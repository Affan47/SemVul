glatex_insert_latex_format(G_GNUC_UNUSED GtkMenuItem * menuitem,
						 G_GNUC_UNUSED gpointer gdata)
{
	gint format = GPOINTER_TO_INT(gdata);
	GeanyDocument *doc = NULL;
	doc = document_get_current();

	if (doc != NULL)
	{
		if (sci_has_selection(doc->editor->sci))
		{
			gchar *selection;
			gchar *replacement = NULL;

			selection = sci_get_selection_contents(doc->editor->sci);

			if (format == LATEX_SMALLCAPS &&
				glatex_lowercase_on_smallcaps == TRUE)
			{
				gchar *new_selection = NULL;
				new_selection = g_utf8_strdown(selection, -1);
				g_free(selection);
				selection = g_strdup(new_selection);
				g_free(new_selection);
			}
			replacement = g_strconcat(glatex_format_pattern[format],"{",
				selection, "}", NULL);

			sci_replace_sel(doc->editor->sci, replacement);
			g_free(selection);
			g_free(replacement);
		}
		else
		{
			sci_start_undo_action(doc->editor->sci);
			glatex_insert_string(glatex_format_pattern[format], TRUE);
			glatex_insert_string("{", TRUE);
			glatex_insert_string("}", FALSE);
			sci_end_undo_action(doc->editor->sci);
		}
	}
}
