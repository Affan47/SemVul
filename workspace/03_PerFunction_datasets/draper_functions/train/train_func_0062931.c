lore_treasure(int m_idx, int num_item, int num_gold)
{
	monster_type *m_ptr = cave_monster(cave, m_idx);
	monster_lore *l_ptr = &l_list[m_ptr->r_idx];


	if (num_item > l_ptr->drop_item) l_ptr->drop_item = num_item;
	if (num_gold > l_ptr->drop_gold) l_ptr->drop_gold = num_gold;


	rf_on(l_ptr->flags, RF_DROP_GOOD);
	rf_on(l_ptr->flags, RF_DROP_GREAT);


	if (p_ptr->monster_race_idx == m_ptr->r_idx)
	{

		p_ptr->redraw |= (PR_MONSTER);
	}
}
