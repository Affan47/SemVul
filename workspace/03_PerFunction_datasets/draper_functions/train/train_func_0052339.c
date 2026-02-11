open_hspell_pipe ()
{
	gboolean bool_hspell_call;


	hspell_standard_input = 0;
	hspell_standard_output = 0;
	hspell_standard_input_channel = NULL;
	hspell_standard_output_channel = NULL;


	bool_hspell_call = g_spawn_async_with_pipes (NULL,
						     hspell_argv,
						     NULL,
						     G_SPAWN_SEARCH_PATH,
						     ChildSetupFunc,
						     NULL,
						     NULL,
						     &hspell_standard_input,
						     &hspell_standard_output,
						     NULL, NULL);

	if (!bool_hspell_call)
		return FALSE;


	hspell_standard_input_channel =
		g_io_channel_unix_new (hspell_standard_input);
	hspell_standard_output_channel =
		g_io_channel_unix_new (hspell_standard_output);


	g_io_channel_set_encoding (hspell_standard_input_channel,
				   "iso8859-8", NULL);
	g_io_channel_set_encoding (hspell_standard_output_channel,
				   "iso8859-8", NULL);

	return TRUE;
}
