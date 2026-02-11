banishment(void)
{
	int i;
	unsigned dam = 0;

	char typ;


	if (!get_com("Choose a monster race (by symbol) to banish: ", &typ))
		return FALSE;


	for (i = 1; i < mon_max; i++)
	{
		monster_type *m_ptr = &mon_list[i];
		monster_race *r_ptr = &r_info[m_ptr->r_idx];


		if (!m_ptr->r_idx) continue;


		if (rf_has(r_ptr->flags, RF_UNIQUE)) continue;


		if (r_ptr->d_char != typ) continue;


		delete_monster_idx(i);


		dam += randint1(4);
	}


	take_hit(dam, "the strain of casting Banishment");


	p_ptr->redraw |= PR_MONLIST;


	return TRUE;
}
