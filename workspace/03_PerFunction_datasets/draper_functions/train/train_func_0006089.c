rd_monster_memory(u32b version)
{
	int r_idx;
	u16b tmp16u;


	rd_u16b(&tmp16u);


	if (tmp16u > z_info->r_max)
	{
		note(format("Too many (%u) monster races!", tmp16u));
		return (-1);
	}


	for (r_idx = 0; r_idx < tmp16u; r_idx++)
	{
		size_t i;

		monster_race *r_ptr = &r_info[r_idx];
		monster_lore *l_ptr = &l_list[r_idx];


		rd_s16b(&l_ptr->sights);
		rd_s16b(&l_ptr->deaths);
		rd_s16b(&l_ptr->pkills);
		rd_s16b(&l_ptr->tkills);


		rd_byte(&l_ptr->wake);
		rd_byte(&l_ptr->ignore);


		rd_byte(&l_ptr->drop_gold);
		rd_byte(&l_ptr->drop_item);


		rd_byte(&l_ptr->cast_innate);
		rd_byte(&l_ptr->cast_spell);


		for (i = 0; i < MONSTER_BLOW_MAX; i++)
			rd_byte(&l_ptr->blows[i]);


		for (i = 0; i < 12 && i < RF_SIZE; i++)
			rd_byte(&l_ptr->flags[i]);
		if (i < 12) strip_bytes(12 - i);


		for (i = 0; i < 12 && i < RSF_SIZE; i++)
			rd_byte(&l_ptr->spell_flags[i]);
		if (i < 12) strip_bytes(12 - i);


		rd_byte(&r_ptr->max_num);


		strip_bytes(3);


		rsf_inter(l_ptr->spell_flags, r_ptr->spell_flags);
	}

	return 0;
}
