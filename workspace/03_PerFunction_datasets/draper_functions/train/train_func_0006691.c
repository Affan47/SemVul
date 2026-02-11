wr_randarts(void)
{
	size_t i, j;

	if (!OPT(adult_randarts))
		return;

	wr_u16b(z_info->a_max);

	for (i = 0; i < z_info->a_max; i++)
	{
		artifact_type *a_ptr = &a_info[i];

		wr_byte(a_ptr->tval);
		wr_byte(a_ptr->sval);
		wr_s16b(a_ptr->pval);

		wr_s16b(a_ptr->to_h);
		wr_s16b(a_ptr->to_d);
		wr_s16b(a_ptr->to_a);
		wr_s16b(a_ptr->ac);

		wr_byte(a_ptr->dd);
		wr_byte(a_ptr->ds);

		wr_s16b(a_ptr->weight);

		wr_s32b(a_ptr->cost);


		for (j = 0; j < 12 && j < OF_SIZE; j++)
			wr_byte(a_ptr->flags[j]);
		if (j < 12) pad_bytes(OF_SIZE - j);

		wr_byte(a_ptr->level);
		wr_byte(a_ptr->rarity);
		wr_byte(a_ptr->alloc_prob);
		wr_byte(a_ptr->alloc_min);
		wr_byte(a_ptr->alloc_max);

		wr_u16b(a_ptr->effect);
		wr_u16b(a_ptr->time.base);
		wr_u16b(a_ptr->time.dice);
		wr_u16b(a_ptr->time.sides);
	}
}
