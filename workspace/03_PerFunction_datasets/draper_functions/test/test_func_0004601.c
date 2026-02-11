add_bound_from_constraint(
	__isl_take isl_basic_set *hull, struct sh_data *data,
	__isl_keep isl_set *set, isl_int *ineq)
{
	int i, k;
	isl_ctx *ctx;
	uint32_t c_hash;
	struct ineq_cmp_data v;

	if (!hull || !set)
		return isl_basic_set_free(hull);

	v.len = isl_basic_set_total_dim(hull);
	v.p = ineq;
	c_hash = isl_seq_get_hash(ineq + 1, v.len);

	ctx = isl_basic_set_get_ctx(hull);
	for (i = 0; i < set->n; ++i) {
		int bound;
		struct isl_hash_table_entry *entry;

		entry = isl_hash_table_find(ctx, data->p[i].table,
						c_hash, &has_ineq, &v, 0);
		if (entry) {
			isl_int *ineq_i = entry->data;
			int neg, more_relaxed;

			neg = isl_seq_is_neg(ineq_i + 1, ineq + 1, v.len);
			if (neg)
				isl_int_neg(ineq_i[0], ineq_i[0]);
			more_relaxed = isl_int_gt(ineq_i[0], ineq[0]);
			if (neg)
				isl_int_neg(ineq_i[0], ineq_i[0]);
			if (more_relaxed)
				break;
			else
				continue;
		}
		bound = is_bound(data, set, i, ineq, 0);
		if (bound < 0)
			return isl_basic_set_free(hull);
		if (!bound)
			break;
	}
	if (i < set->n)
		return hull;

	k = isl_basic_set_alloc_inequality(hull);
	if (k < 0)
		return isl_basic_set_free(hull);
	isl_seq_cpy(hull->ineq[k], ineq, 1 + v.len);

	return hull;
}
