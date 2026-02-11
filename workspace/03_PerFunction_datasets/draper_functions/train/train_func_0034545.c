defining_equality(__isl_keep isl_basic_map *eq,
	__isl_keep isl_space *dim, enum isl_dim_type type, int pos)
{
	int i;
	unsigned total;

	if (!eq)
		return -1;

	pos += isl_space_offset(dim, type);
	total = isl_basic_map_total_dim(eq);

	for (i = 0; i < eq->n_eq; ++i) {
		if (isl_seq_last_non_zero(eq->eq[i] + 1, total) != pos)
			continue;
		if (isl_int_is_one(eq->eq[i][1 + pos]))
			isl_seq_neg(eq->eq[i], eq->eq[i], 1 + total);
		return i;
	}

	return -1;
}
