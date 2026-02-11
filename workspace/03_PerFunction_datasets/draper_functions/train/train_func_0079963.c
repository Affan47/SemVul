compressed_seq_generate(compressed_seq_t * cs, cmph_uint32 * vals_table, cmph_uint32 n)
{
	register cmph_uint32 i;

	register cmph_uint32 * lengths = (cmph_uint32 *)calloc(n, sizeof(cmph_uint32));
	register cmph_uint32 rems_mask;
	register cmph_uint32 stored_value;

	cs->n = n;
	cs->total_length = 0;

	for(i = 0; i < cs->n; i++)
	{
		if(vals_table[i] == 0)
		{
			lengths[i] = 0;
		}
		else
		{
			lengths[i] = compressed_seq_i_log2(vals_table[i] + 1);
			cs->total_length += lengths[i];
		};
	};

	if(cs->store_table)
	{
		free(cs->store_table);
	}
	cs->store_table = (cmph_uint32 *) calloc(((cs->total_length + 31) >> 5), sizeof(cmph_uint32));
	cs->total_length = 0;

	for(i = 0; i < cs->n; i++)
	{
		if(vals_table[i] == 0)
			continue;
		stored_value = vals_table[i] - ((1U << lengths[i]) - 1U);
		set_bits_at_pos(cs->store_table, cs->total_length, stored_value, lengths[i]);
		cs->total_length += lengths[i];
	};

	cs->rem_r = compressed_seq_i_log2(cs->total_length/cs->n);

	if(cs->rem_r == 0)
	{
		cs->rem_r = 1;
	}

	if(cs->length_rems)
	{
		free(cs->length_rems);
	}

	cs->length_rems = (cmph_uint32 *) calloc(BITS_TABLE_SIZE(cs->n, cs->rem_r), sizeof(cmph_uint32));

	rems_mask = (1U << cs->rem_r) - 1U;
	cs->total_length = 0;

	for(i = 0; i < cs->n; i++)
	{
		cs->total_length += lengths[i];
		set_bits_value(cs->length_rems, i, cs->total_length & rems_mask, cs->rem_r, rems_mask);
		lengths[i] = cs->total_length >> cs->rem_r;
	};

	select_init(&cs->sel);


	select_generate(&cs->sel, lengths, cs->n, (cs->total_length >> cs->rem_r));

	free(lengths);
}
