recalculate_stats(int *stats, int points_left)
{
	int i;


	for (i = 0; i < A_MAX; i++)
	{

		if (OPT(birth_maximize))
		{

			p_ptr->stat_cur[i] = p_ptr->stat_max[i] =
				p_ptr->stat_birth[i] = stats[i];
		}


		else
		{

			int bonus = p_ptr->race->r_adj[i] + p_ptr->class->c_adj[i];


			p_ptr->stat_cur[i] = p_ptr->stat_max[i] =
				p_ptr->stat_birth[i] =
				modify_stat_value(stats[i], bonus);
		}
	}


	p_ptr->au_birth = STARTING_GOLD + (50 * points_left);


	get_bonuses();


	event_signal(EVENT_GOLD);
	event_signal(EVENT_AC);
	event_signal(EVENT_HP);
	event_signal(EVENT_STATS);
}
