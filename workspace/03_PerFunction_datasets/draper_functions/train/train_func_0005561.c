compact_monsters_aux(int i1, int i2)
{
	int y, x;

	monster_type *m_ptr;

	s16b this_o_idx, next_o_idx = 0;


	if (i1 == i2) return;


	m_ptr = cave_monster(cave, i1);


	y = m_ptr->fy;
	x = m_ptr->fx;


	cave->m_idx[y][x] = i2;


	m_ptr->midx = i2;


	for (this_o_idx = m_ptr->hold_o_idx; this_o_idx; this_o_idx = next_o_idx)
	{
		object_type *o_ptr;


		o_ptr = object_byid(this_o_idx);


		next_o_idx = o_ptr->next_o_idx;


		o_ptr->held_m_idx = i2;
	}


	if (m_ptr->mimicked_o_idx > 0) {

		object_type *o_ptr;


		o_ptr = object_byid(m_ptr->mimicked_o_idx);


		o_ptr->mimicking_m_idx = i2;
	}


	if (target_get_monster() == i1) target_set_monster(i2);


	if (p_ptr->health_who == i1) p_ptr->health_who = i2;


	COPY(cave_monster(cave, i2), cave_monster(cave, i1), struct monster);


	(void)WIPE(cave_monster(cave, i1), monster_type);
}
