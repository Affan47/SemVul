gth_script_get_command_line (GthScript  *script,
			     GtkWindow  *parent,
			     GList      *file_list ,
			     GError    **error)
{
	ReplaceData  *replace_data;
	GRegex       *qre;
	GRegex       *re;
	char        **a;
	GString      *command_line;
	int           i;
	char         *result;

	replace_data = g_new0 (ReplaceData, 1);
	replace_data->parent = parent;
	replace_data->script = script;
	replace_data->file_list = file_list;
	replace_data->error = error;

	re = g_regex_new ("%U|%F|%B|%N|%E|%P|%ask(\\{[^}]+\\}(\\{[^}]+\\})?)?|%attr\\{[^}]+\\}", 0, 0, NULL);

	replace_data->quote_values = FALSE;
	command_line = g_string_new ("");
	qre = g_regex_new ("%quote\\{([^}]+)\\}", 0, 0, NULL);
	a = g_regex_split (qre, script->priv->command, 0);
	for (i = 0; a[i] != NULL; i++) {
		if (i % 2 == 1) {
			char *sub_result;
			char *quoted;

			sub_result = g_regex_replace_eval (re, a[i], -1, 0, 0, command_line_eval_cb, replace_data, error);
			quoted = g_shell_quote (g_strstrip (sub_result));
			g_string_append (command_line, quoted);

			g_free (quoted);
			g_free (sub_result);
		}
		else
			g_string_append (command_line, a[i]);
	}

	replace_data->quote_values = TRUE;
	result = g_regex_replace_eval (re, command_line->str, -1, 0, 0, command_line_eval_cb, replace_data, error);

	g_free (replace_data);
	g_string_free (command_line, TRUE);
	g_regex_unref (qre);
	g_regex_unref (re);

	return result;
}
