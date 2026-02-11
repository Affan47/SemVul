get_aim_dir(int *dp)
{

	int dir = 0;

	ui_event_data ke;

	cptr p;


	(*dp) = 0;


	if (OPT(use_old_target) && target_okay() && !dir) dir = 5;


	while (!dir)
	{

		if (!target_okay())
			p = "Direction ('*' or <click> to target, \"'\" for closest, Escape to cancel)? ";
		else
			p = "Direction ('5' for target, '*' or <click> to re-target, Escape to cancel)? ";


		if (!get_com_ex(p, &ke)) break;


		switch (ke.key)
		{

			case '\xff':
			{
				if (target_set_interactive(TARGET_KILL, KEY_GRID_X(ke), KEY_GRID_Y(ke)))
					dir = 5;

				break;
			}


			case '*':
			{
				if (target_set_interactive(TARGET_KILL, -1, -1)) dir = 5;
				break;
			}


			case '\'':
			{
				if (target_set_closest(TARGET_KILL)) dir = 5;
				break;
			}


			case 't':
			case '5':
			case '0':
			case '.':
			{
				if (target_okay()) dir = 5;
				break;
			}


			default:
			{
				int keypresses_handled = 0;

				while (ke.key != 0)
				{
					int this_dir;


					this_dir = target_dir(ke.key);

					if (this_dir)
					{
						dir = dir_transitions[dir][this_dir];
					}
					else
					{
						break;
					}

					if (lazymove_delay == 0 || ++keypresses_handled > 1)
						break;


					inkey_scan = lazymove_delay;
					ke = inkey_ex();
				}
			}
		}


		if (!dir) bell("Illegal aim direction!");
	}


	if (!dir) return (FALSE);


	(*dp) = dir;


	if (p_ptr->timed[TMD_CONFUSED])
	{

		dir = ddd[randint0(8)];
	}


	if ((*dp) != dir)
	{

		msg_print("You are confused.");
	}


	(*dp) = dir;


	return (TRUE);
}
