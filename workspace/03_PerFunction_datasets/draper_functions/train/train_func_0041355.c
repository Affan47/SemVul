mission_load(char *filename_ext)
{
	char filename[128], *ext;

	if ( (filename_ext != NULL) && (Game_current_mission_filename != filename_ext) )
		strncpy(Game_current_mission_filename, filename_ext, MAX_FILENAME_LEN-1);

	mprintf(("MISSION LOAD: '%s'\n", filename_ext));

	strncpy(filename, filename_ext, 127);
	ext = strrchr(filename, '.');
	if (ext) {
		mprintf(( "Hmmm... Extension passed to mission_load...\n" ));
		*ext = 0;
	}

	strcat_s(filename, FS_MISSION_FILE_EXT);


	if ( parse_main(filename) )
		return -1;

	if (Select_default_ship) {
		int ret;
		ret = create_default_player_ship();
		Assert(!ret);
	}

	ml_update_recent_missions(filename_ext);

	init_hud();
	return 0;
}
