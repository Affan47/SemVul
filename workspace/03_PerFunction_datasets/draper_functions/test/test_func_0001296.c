cheat_monster_lore(int r_idx, monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	int i;


	l_ptr->tkills = MAX_SHORT;


	l_ptr->wake = l_ptr->ignore = MAX_UCHAR;


	for (i = 0; i < MONSTER_BLOW_MAX; i++)
	{

		if (r_ptr->blow[i].effect || r_ptr->blow[i].method)
		{

			l_ptr->blows[i] = MAX_UCHAR;
		}
	}


	l_ptr->drop_item = 0;

	if (rf_has(r_ptr->flags, RF_DROP_4))
		l_ptr->drop_item += 6;
	if (rf_has(r_ptr->flags, RF_DROP_3))
		l_ptr->drop_item += 4;
	if (rf_has(r_ptr->flags, RF_DROP_2))
		l_ptr->drop_item += 3;
	if (rf_has(r_ptr->flags, RF_DROP_1))
		l_ptr->drop_item++;

	if (rf_has(r_ptr->flags, RF_DROP_40))
		l_ptr->drop_item++;
	if (rf_has(r_ptr->flags, RF_DROP_60))
		l_ptr->drop_item++;

	l_ptr->drop_gold = l_ptr->drop_item;


	if (rf_has(r_ptr->flags, RF_ONLY_GOLD)) l_ptr->drop_item = 0;
	if (rf_has(r_ptr->flags, RF_ONLY_ITEM)) l_ptr->drop_gold = 0;


	l_ptr->cast_innate = MAX_UCHAR;
	l_ptr->cast_spell = MAX_UCHAR;


	rf_setall(l_ptr->flags);
	rsf_copy(l_ptr->spell_flags, r_ptr->spell_flags);
}
