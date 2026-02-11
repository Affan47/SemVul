poly_r_idx(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];

	int i, r, lev1, lev2;


	if (rf_has(r_ptr->flags, RF_UNIQUE)) return (r_idx);


	lev1 = r_ptr->level - ((randint1(20)/randint1(9))+1);
	lev2 = r_ptr->level + ((randint1(20)/randint1(9))+1);


	for (i = 0; i < 1000; i++)
	{

		r = get_mon_num((p_ptr->depth + r_ptr->level) / 2 + 5);


		if (!r) break;


		r_ptr = &r_info[r];


		if (rf_has(r_ptr->flags, RF_UNIQUE)) continue;


		if ((r_ptr->level < lev1) || (r_ptr->level > lev2)) continue;


		r_idx = r;


		break;
	}


	return (r_idx);
}
