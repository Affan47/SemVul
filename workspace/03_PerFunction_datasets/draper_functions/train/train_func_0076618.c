compact_monsters(int size)
{
	int i, num, cnt;

	int cur_lev, cur_dis, chance;


	if (size) msg_print("Compacting monsters...");


	for (num = 0, cnt = 1; num < size; cnt++)
	{

		cur_lev = 5 * cnt;


		cur_dis = 5 * (20 - cnt);


		for (i = 1; i < mon_max; i++)
		{
			monster_type *m_ptr = &mon_list[i];

			monster_race *r_ptr = &r_info[m_ptr->r_idx];


			if (!m_ptr->r_idx) continue;


			if (r_ptr->level > cur_lev) continue;


			if ((cur_dis > 0) && (m_ptr->cdis < cur_dis)) continue;


			chance = 90;


			if (rf_has(r_ptr->flags, RF_QUESTOR) && (cnt < 1000)) chance = 100;


			if (rf_has(r_ptr->flags, RF_UNIQUE)) chance = 99;


			if (randint0(100) < chance) continue;


			delete_monster_idx(i);


			num++;
		}
	}


	for (i = mon_max - 1; i >= 1; i--)
	{

		monster_type *m_ptr = &mon_list[i];


		if (m_ptr->r_idx) continue;


		compact_monsters_aux(mon_max - 1, i);


		mon_max--;
	}
}
