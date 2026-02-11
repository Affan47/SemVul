sig_complete_word(GList **list, WINDOW_REC *window,
			      const char *word, const char *linestart,
			      int *want_space)
{
	const char *newword, *cmdchars;
	char *signal, *cmd, *args, *line;

	g_return_if_fail(list != NULL);
	g_return_if_fail(word != NULL);
	g_return_if_fail(linestart != NULL);


	newword = completion_find(word, FALSE);
	if (newword != NULL) {
		*list = g_list_append(*list, g_strdup(newword));

		signal_stop();
		return;
	}

	if (*linestart != '\0' && (*word == '/' || *word == '~')) {

		*list = g_list_concat(*list, filename_complete(word, NULL));
		if (*list != NULL) {
			*want_space = FALSE;
			signal_stop();
			return;
		}
	}


	cmdchars = settings_get_str("cmdchars");
	if (*word != '\0' && *linestart == '\0' && strchr(cmdchars, *word)) {

		*list = completion_get_commands(word+1, *word);


		*list = g_list_concat(*list,
				      completion_get_aliases(word+1, *word));

		if (*list != NULL) signal_stop();
		return;
	}


	if (*linestart == '\0')
		return;

        cmdchars = strchr(cmdchars, *linestart);
	if (cmdchars == NULL) return;


	line = linestart[1] == *cmdchars ? g_strdup(linestart+2) :
		expand_aliases(linestart+1);

	cmd = line_get_command(line, &args, FALSE);
	if (cmd == NULL) {
		g_free(line);
		return;
	}


	if (*word == '-') {
		*list = completion_get_options(cmd, word+1);
		if (*list != NULL) signal_stop();
		g_free(cmd);
		g_free(line);
		return;
	}


	signal = g_strconcat("complete command ", cmd, NULL);
	signal_emit(signal, 5, list, window, word, args, want_space);

	if (command_have_sub(line)) {

		g_free(cmd);
		cmd = g_strconcat(line, " ", word, NULL);
		*list = g_list_concat(completion_get_subcommands(cmd), *list);
	}

	if (*list != NULL) signal_stop();
	g_free(signal);
	g_free(cmd);
	g_free(line);
}
