point_based_command(void)
{
	static int stat = 0;
	struct keypress ch;
	enum birth_stage next = BIRTH_POINTBASED;


	Term_gotoxy(COSTS_COL + 4, COSTS_ROW + stat);


	ch = inkey();

	if (ch.code == KTRL('X'))
	{
		cmd_insert(CMD_QUIT);
		next = BIRTH_COMPLETE;
	}


	else if (ch.code == ESCAPE)
	{
		next = BIRTH_BACK;
	}

	else if (ch.code == 'r' || ch.code == 'R')
	{
		cmd_insert(CMD_RESET_STATS);
		cmd_set_arg_choice(cmd_get_top(), 0, FALSE);
	}


	else if ((ch.code == '\r') || (ch.code == '\n'))
	{
		next = BIRTH_NAME_CHOICE;
	}
	else
	{
		int dir = target_dir(ch);


		if (dir == 8)
			stat = (stat + A_MAX - 1) % A_MAX;


		if (dir == 2)
			stat = (stat + 1) % A_MAX;


		if (dir == 4)
		{
			cmd_insert(CMD_SELL_STAT);
			cmd_set_arg_choice(cmd_get_top(), 0, stat);
		}


		if (dir == 6)
		{
			cmd_insert(CMD_BUY_STAT);
			cmd_set_arg_choice(cmd_get_top(), 0, stat);
		}
	}

	return next;
}
