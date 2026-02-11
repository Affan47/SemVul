on_debug_tree_inspect (GtkAction *action, gpointer user_data)
{
	ExprWatch * ew = (ExprWatch *)user_data;
	IAnjutaEditor *te = NULL;
	gchar *expression = NULL;


	te = dma_get_current_editor (ANJUTA_PLUGIN (ew->plugin));
	if (te == NULL)	return;

	expression = ianjuta_editor_selection_get (IANJUTA_EDITOR_SELECTION (te), NULL);
	if (expression == NULL)
	{
		expression = ianjuta_editor_get_current_word (IANJUTA_EDITOR (te), NULL);
	}
	if (g_regex_match_simple("^\\s*$", expression,G_REGEX_MULTILINE | G_REGEX_DOLLAR_ENDONLY, G_REGEX_MATCH_ANCHORED))
	{
		expression = NULL;
	}

	debug_tree_inspect_evaluate_dialog (ew, expression);
	g_free (expression);
}
