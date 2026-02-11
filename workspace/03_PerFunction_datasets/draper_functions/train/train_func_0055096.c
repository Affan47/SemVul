player_init(struct player *p)
{
	int i;

	if (p->inventory)
		mem_free(p->inventory);


	(void)WIPE(p, struct player);


	for (i = 0; z_info && i < z_info->a_max; i++)
	{
		artifact_type *a_ptr = &a_info[i];
		a_ptr->created = FALSE;
		a_ptr->seen = FALSE;
	}


	for (i = 0; q_list && i < MAX_Q_IDX; i++)
	{
		q_list[i].level = 0;
	}

	if (q_list) {
		q_list[0].level = 99;
		q_list[1].level = 100;
	}

	for (i = 1; z_info && i < z_info->k_max; i++) {
		object_kind *k_ptr = &k_info[i];
		k_ptr->tried = FALSE;
		k_ptr->aware = FALSE;
	}

	for (i = 1; z_info && i < z_info->r_max; i++)
	{
		monster_race *r_ptr = &r_info[i];
		monster_lore *l_ptr = &l_list[i];
		r_ptr->cur_num = 0;
		r_ptr->max_num = 100;
		if (rf_has(r_ptr->flags, RF_UNIQUE))
			r_ptr->max_num = 1;
		l_ptr->pkills = 0;
	}


	if (z_info)
		r_info[z_info->r_max-1].max_num = 0;


	p->food = PY_FOOD_FULL - 1;


	for (i = 0; i < PY_MAX_SPELLS; i++)
		p->spell_order[i] = 99;

	p->inventory = C_ZNEW(ALL_INVEN_TOTAL, struct object);


	turn = 1;
	p_ptr->total_energy = 0;
	p_ptr->resting_turn = 0;

	p_ptr->race = races;
	p_ptr->class = classes;
}
