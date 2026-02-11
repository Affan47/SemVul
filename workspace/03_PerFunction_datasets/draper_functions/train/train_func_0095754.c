ui_check_who_won()
{
	char *line, *who_str = NULL;
	int who, len;
	if (!move_fout)
		return;
	fprintf (move_fout, "WHO_WON \n");
	fflush (move_fout);
	line = line_read(move_fin);
	if (g_strncasecmp(line, "ACK", 3))
	{

		ui_gameover = FALSE;
		sb_set_score ("");
		return;
	}
	line += 4;
	line = g_strstrip(line);
	who_str = line;
	while(!isspace(*line) && *line) line++;
	while(isspace(*line)) line++;
	sb_set_score (line);
	if (!g_strncasecmp(who_str, "NYET", 4))
	{
		ui_gameover = FALSE;
		return;
	}
	ui_stopped = TRUE;
	ui_gameover = TRUE;
	if (opt_logfile)
		fprintf(opt_logfile, "RESULT: %s\n", who_str);
	if (!state_gui_active)
		ui_cleanup();
	sb_update ();
	if (game_single_player && !ui_cheated && !g_strncasecmp(who_str, "WON", 3))
	{
		gboolean retval;
		retval = prefs_add_highscore (line, sb_get_human_time ());
		if (retval)
			sound_play (SOUND_HIGHSCORE);
		else
			sound_play (SOUND_WON);
		if (game_levels)
		{
			GameLevel *next_level = game_levels;
			while (next_level->name)
			{
				if (next_level->game == opt_game)
					break;
				next_level++;
			}
			next_level++;
			if (next_level->name)
				menu_put_level (next_level->name);
		}
	}
	if (game_single_player && !ui_cheated && !g_strncasecmp(who_str, "LOST", 4))
		sound_play (SOUND_LOST);
}
