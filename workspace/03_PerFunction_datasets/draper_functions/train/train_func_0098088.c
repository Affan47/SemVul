add_strides(__isl_take isl_basic_set *bset,
	__isl_keep isl_morph *morph)
{
	int i, div, k;
	isl_int gcd;

	if (isl_int_is_one(morph->inv->row[0][0]))
		return bset;

	isl_int_init(gcd);

	for (i = 0; 1 + i < morph->inv->n_row; ++i) {
		isl_seq_gcd(morph->inv->row[1 + i], morph->inv->n_col, &gcd);
		if (isl_int_is_divisible_by(gcd, morph->inv->row[0][0]))
			continue;
		div = isl_basic_set_alloc_div(bset);
		if (div < 0)
			goto error;
		isl_int_set_si(bset->div[div][0], 0);
		k = isl_basic_set_alloc_equality(bset);
		if (k < 0)
			goto error;
		isl_seq_cpy(bset->eq[k], morph->inv->row[1 + i],
			    morph->inv->n_col);
		isl_seq_clr(bset->eq[k] + morph->inv->n_col, bset->n_div);
		isl_int_set(bset->eq[k][morph->inv->n_col + div],
			    morph->inv->row[0][0]);
	}

	isl_int_clear(gcd);

	return bset;
error:
	isl_int_clear(gcd);
	isl_basic_set_free(bset);
	return NULL;
}
