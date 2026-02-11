wipe_mon_list(void)
{
	int i;


	for (i = mon_max - 1; i >= 1; i--)
	{
		monster_type *m_ptr = &mon_list[i];

		monster_race *r_ptr = &r_info[m_ptr->r_idx];


		if (!m_ptr->r_idx) continue;


		r_ptr->cur_num--;


		cave_m_idx[m_ptr->fy][m_ptr->fx] = 0;


		(void)WIPE(m_ptr, monster_type);
	}


	mon_max = 1;


	mon_cnt = 0;


	num_repro = 0;


	target_set_monster(0);


	health_track(0);
}
