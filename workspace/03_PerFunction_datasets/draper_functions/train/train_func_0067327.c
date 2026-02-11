textui_action_menu_choose(void)
{
	region area = { 21, 5, 37, 6 };

	struct cmd_info chosen_command = { 0 };

	if (!command_menu)
		command_menu = menu_new(MN_SKIN_SCROLL, &command_menu_iter);

	menu_setpriv(command_menu, N_ELEMENTS(cmds_all) - 1, &chosen_command);
	menu_layout(command_menu, &area);


	screen_save();
	window_make(19, 4, 58, 11);

	menu_select(command_menu, 0, TRUE);

	screen_load();

	return chosen_command.key;
}
