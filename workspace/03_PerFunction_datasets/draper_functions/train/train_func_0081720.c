do_cmd_open(cmd_code code, cmd_arg args[])
{
	int y, x, dir;

	s16b o_idx;

	bool more = FALSE;

	dir = args[0].direction;


	y = p_ptr->py + ddy[dir];
	x = p_ptr->px + ddx[dir];


	o_idx = chest_check(y, x);


	if (!o_idx && !do_cmd_open_test(y, x))
	{

		disturb(p_ptr, 0, 0);
		return;
	}


	p_ptr->energy_use = 100;


	if (player_confuse_dir(p_ptr, &dir, FALSE))
	{

		y = p_ptr->py + ddy[dir];
		x = p_ptr->px + ddx[dir];


		o_idx = chest_check(y, x);
	}


	if (cave->m_idx[y][x] > 0)
	{
		int m_idx = cave->m_idx[y][x];


		if (is_mimicking(m_idx)) {
			become_aware(m_idx);


			mon_clear_timed(m_idx, MON_TMD_SLEEP, MON_TMD_FLG_NOMESSAGE, FALSE);
		} else {

			msg("There is a monster in the way!");


			py_attack(y, x);
		}
	}


	else if (o_idx)
	{

		more = do_cmd_open_chest(y, x, o_idx);
	}


	else
	{

		more = do_cmd_open_aux(y, x);
	}


	if (!more) disturb(p_ptr, 0, 0);
}
