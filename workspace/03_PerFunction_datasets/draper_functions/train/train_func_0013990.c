fuzzy_command_match (const char *cmd1,
		     const char *cmd2,
		     gboolean   *fuzzy)
{
	char **tokens;
	char  *word1, *word2;

	g_return_val_if_fail (cmd1 && cmd2, TRUE);

	*fuzzy = FALSE;

	if (!strcmp (cmd1, cmd2))
		return TRUE;


	tokens = g_strsplit (cmd1, " ", -1);
	if (!tokens || !tokens [0]) {
		g_strfreev (tokens);
		return FALSE;
	}

	word1 = g_path_get_basename (tokens [0]);
	g_strfreev (tokens);


	tokens = g_strsplit (cmd2, " ", -1);
	word2 = g_path_get_basename (tokens [0]);
	if (!tokens || !tokens [0]) {
		g_free (word1);
		g_strfreev (tokens);
		return FALSE;
	}

	g_strfreev (tokens);

	if (!strcmp (word1, word2)) {
		g_free (word1);
		g_free (word2);
		*fuzzy = TRUE;
		return TRUE;
	}

	g_free (word1);
	g_free (word2);

	return FALSE;
}
