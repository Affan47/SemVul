prepare_level_editor()
{
	game_root_mode = ROOT_IS_LVLEDIT;
	skip_initial_menus = 1;
	char fp[2048];
	find_file("levels.dat", MAP_DIR, fp, 0);
	LoadShip(fp, 0);
	PrepareStartOfNewCharacter("NewTuxStartGameSquare");
	skip_initial_menus = 0;
	free(Me.character_name);
	Me.character_name = strdup("MapEd");
}
