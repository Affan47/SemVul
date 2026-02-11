menu_question(enum birth_stage current, menu_type *current_menu, cmd_code choice_command)
{
	struct birthmenu_data *menu_data = menu_priv(current_menu);
	ui_event cx;

	enum birth_stage next = BIRTH_RESET;


	clear_question();
	Term_putstr(QUESTION_COL, QUESTION_ROW, -1, TERM_YELLOW, menu_data->hint);

	current_menu->cmd_keys = "?=*\x18";

	while (next == BIRTH_RESET)
	{

		cx = menu_select(current_menu, EVT_KBRD, FALSE);


		if (cx.type == EVT_ESCAPE)
		{
			next = BIRTH_BACK;
		}
		else if (cx.type == EVT_SELECT)
		{
			if (current == BIRTH_ROLLER_CHOICE)
			{
				cmd_insert(CMD_FINALIZE_OPTIONS);

				if (current_menu->cursor)
				{

					cmd_insert(CMD_ROLL_STATS);
					next = current + 2;
				}
				else
				{


					point_based_start();
					cmd_insert(CMD_RESET_STATS);
					cmd_set_arg_choice(cmd_get_top(), 0, TRUE);
					next = current + 1;
				}
			}
			else
			{
				cmd_insert(choice_command);
				cmd_set_arg_choice(cmd_get_top(), 0, current_menu->cursor);
				next = current + 1;
			}
		}
		else if (cx.type == EVT_KBRD)
		{

			if (cx.key.code == '*' && menu_data->allow_random)
			{
				current_menu->cursor = randint0(current_menu->count);
				cmd_insert(choice_command);
				cmd_set_arg_choice(cmd_get_top(), 0, current_menu->cursor);

				menu_refresh(current_menu, FALSE);
				next = current + 1;
			}
			else if (cx.key.code == '=')
			{
				do_cmd_options_birth();
				next = current;
			}
			else if (cx.key.code == KTRL('X'))
			{
				cmd_insert(CMD_QUIT);
				next = BIRTH_COMPLETE;
			}
			else if (cx.key.code == '?')
			{
				do_cmd_help();
			}
		}
	}

	return next;
}
