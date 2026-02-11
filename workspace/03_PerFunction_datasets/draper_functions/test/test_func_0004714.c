wr_item(const object_type *o_ptr)
{
	size_t i, j;

	wr_u16b(0xffff);
	wr_byte(ITEM_VERSION);

	wr_s16b(0);


	wr_byte(o_ptr->iy);
	wr_byte(o_ptr->ix);

	wr_byte(o_ptr->tval);
	wr_byte(o_ptr->sval);

        for (i = 0; i < MAX_PVALS; i++) {
		wr_s16b(o_ptr->pval[i]);
        }
        wr_byte(o_ptr->num_pvals);

	wr_byte(0);

	wr_byte(o_ptr->number);
	wr_s16b(o_ptr->weight);

	if (o_ptr->artifact) wr_byte(o_ptr->artifact->aidx);
	else wr_byte(0);

	if (o_ptr->ego) wr_byte(o_ptr->ego->eidx);
	else wr_byte(0);

	wr_s16b(o_ptr->timeout);

	wr_s16b(o_ptr->to_h);
	wr_s16b(o_ptr->to_d);
	wr_s16b(o_ptr->to_a);
	wr_s16b(o_ptr->ac);
	wr_byte(o_ptr->dd);
	wr_byte(o_ptr->ds);

	wr_u16b(o_ptr->ident);

	wr_byte(o_ptr->marked);

	wr_byte(o_ptr->origin);
	wr_byte(o_ptr->origin_depth);
	wr_u16b(o_ptr->origin_xtra);

	for (i = 0; i < OF_BYTES && i < OF_SIZE; i++)
		wr_byte(o_ptr->flags[i]);
	if (i < OF_BYTES) pad_bytes(OF_BYTES - i);

	for (i = 0; i < OF_BYTES && i < OF_SIZE; i++)
		wr_byte(o_ptr->known_flags[i]);
	if (i < OF_BYTES) pad_bytes(OF_BYTES - i);

	for (j = 0; j < MAX_PVALS; j++) {
		for (i = 0; i < OF_BYTES && i < OF_SIZE; i++)
			wr_byte(o_ptr->pval_flags[j][i]);
		if (i < OF_BYTES) pad_bytes(OF_BYTES - i);
	}


	wr_s16b(o_ptr->held_m_idx);

	wr_s16b(o_ptr->mimicking_m_idx);


	if (o_ptr->note)
	{
		wr_string(quark_str(o_ptr->note));
	}
	else
	{
		wr_string("");
	}
}
