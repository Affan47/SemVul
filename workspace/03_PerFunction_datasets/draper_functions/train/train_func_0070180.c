load_saved_game(int use_backup)
{
	char version_check_string[1000];
	char *LoadGameData = NULL;
	char filename[1000], prefix[1000];
	FILE *DataFile;

	if (!our_config_dir) {
		DebugPrintf(0, "No Configuration-directory, cannot load any games\n");
		return (OK);
	}

	CenteredPutStringFont(Screen, Menu_BFont, 10, _("Loading"));
	our_SDL_flip_wrapper();

	DebugPrintf(SAVE_LOAD_GAME_DEBUG, "\n%s(): function call confirmed....", __FUNCTION__);

	Activate_Conservative_Frame_Computation();

	reset_lua_state();

	sprintf(prefix, "%s/%s", our_config_dir, Me.character_name);
	if (use_backup) {
		strcat(prefix, ".bkp");
	}

	sprintf(filename, "%s%s", prefix, ".shp");

	if ((DataFile = fopen(filename, "rb")) == NULL) {
		alert_window(_("W A R N I N G !\n\nFreedroidRPG was unable to locate the saved game file you requested to load.\nThis might mean that it really isn't there cause you tried to load a game without ever having saved the game before.\nThe other explanation of this error might be a severe error in FreedroidRPG. If you think this is the case, please report this to the developers."));
		append_new_game_message(_("Failed to load old game."));
		return (ERR);
	} else {
		fclose(DataFile);
		DebugPrintf(1, "\nThe saved game file (.shp file) seems to be there at least.....");
	}
	if (setjmp(saveload_jmpbuf)) {
		if (LoadGameData != NULL)
			free((char *)LoadGameData);
		LoadGameData = NULL;
		return (ERR);
	}

	LoadShip(filename, 1);

	sprintf(filename, "%s%s", prefix, SAVEDGAME_EXT);
	DataFile = fopen(filename, "rb");
	if (inflate_stream(DataFile, (unsigned char **)&LoadGameData, NULL)) {
		fclose(DataFile);
		alert_window("Unable to decompress saved game - this is probably an old, incompatible game. Sorry.");
		return ERR;
	}
	fclose(DataFile);

	clear_out_arrays_for_fresh_game();
	load_game_data(LoadGameData);

	free(LoadGameData);
	LoadGameData = NULL;

	sprintf(version_check_string, "%s;sizeof(tux_t)=%d;sizeof(enemy)=%d;sizeof(bullet)=%d;MAXBULLETS=%d",
		VERSION, (int)sizeof(tux_t), (int)sizeof(enemy), (int)sizeof(bullet), (int)MAXBULLETS);

	if (strcmp(Me.savegame_version_string, version_check_string) != 0) {
		alert_window(_("Version or structsize mismatch! The savegame is not from the same version of FreedroidRPG... possible breakage."));
		our_SDL_flip_wrapper();
		while (!MouseLeftPressed())
			SDL_Delay(1);
	}


	reset_visible_levels();
	get_visible_levels();

	enemy *erot;
	BROWSE_DEAD_BOTS(erot) {


		if (!level_is_visible(erot->pos.z))
			erot->animation_type = DEAD_ANIMATION;
	}


	CountNumberOfDroidsOnShip();

	SwitchBackgroundMusicTo(curShip.AllLevels[Me.pos.z]->Background_Song_Name);


	GameOver = FALSE;

	DebugPrintf(SAVE_LOAD_GAME_DEBUG, "\n%s(): end of function reached.", __FUNCTION__);


	PutStringFont(Screen, FPS_Display_BFont, 75, 150, _("Updating Tux images (this may take a little while...)"));
	our_SDL_flip_wrapper();

	animation_timeline_reset();
	widget_text_init(message_log, _("--- Message Log ---"));
	append_new_game_message(_("Game loaded."));
	return OK;
}
