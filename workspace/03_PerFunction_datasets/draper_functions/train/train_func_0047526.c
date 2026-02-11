on_context_action1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	gchar *word, *command;
	GError *error = NULL;
	GeanyDocument *doc = document_get_current();

	g_return_if_fail(doc != NULL);

	if (sci_has_selection(doc->editor->sci))
	{
		word = g_malloc(sci_get_selected_text_length(doc->editor->sci) + 1);
		sci_get_selected_text(doc->editor->sci, word);
	}
	else
	{
		word = g_strdup(editor_info.current_word);
	}


	if (doc->file_type != NULL &&
		NZV(doc->file_type->context_action_cmd))
	{
		command = g_strdup(doc->file_type->context_action_cmd);
	}
	else
	{
		command = g_strdup(tool_prefs.context_action_cmd);
	}


	if (G_LIKELY(NZV(command)))
	{
		utils_str_replace_all(&command, "%s", word);

		if (! g_spawn_command_line_async(command, &error))
		{
			ui_set_statusbar(TRUE, "Context action command failed: %s", error->message);
			g_error_free(error);
		}
	}
	g_free(word);
	g_free(command);
}
