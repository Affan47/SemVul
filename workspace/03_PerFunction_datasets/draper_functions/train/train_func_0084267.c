html_help_gen ()
{
	int i;
	char dirbuf[1024];
	if (getcwd (dirbuf, 1024) && strcmp (basename (dirbuf), "games"))
	{
		fprintf (stderr, "To generate html help, you must be in the \"games\" directory.\n");
		exit (1);
	}
	if (opt_game)
	{
		html_help_gen_game (opt_game);
		return;
	}
	html_help_gen_gamelist ();
	for (i=0; i<num_games; i++)
		html_help_gen_game (games[i]);
}
