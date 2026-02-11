remove_shifted_constraints(
	struct isl_basic_set *bset, struct isl_basic_set *context)
{
	unsigned int size;
	isl_int ***index;
	int bits;
	int k, h, l;
	isl_ctx *ctx;

	if (!bset)
		return NULL;

	size = round_up(4 * (context->n_ineq+1) / 3 - 1);
	if (size == 0)
		return bset;
	bits = ffs(size) - 1;
	ctx = isl_basic_set_get_ctx(bset);
	index = isl_calloc_array(ctx, isl_int **, size);
	if (!index)
		return bset;

	for (k = 0; k < context->n_ineq; ++k) {
		h = set_hash_index(index, size, bits, context, k);
		index[h] = &context->ineq[k];
	}
	for (k = 0; k < bset->n_ineq; ++k) {
		h = set_hash_index(index, size, bits, bset, k);
		if (!index[h])
			continue;
		l = index[h] - &context->ineq[0];
		if (isl_int_lt(bset->ineq[k][0], context->ineq[l][0]))
			continue;
		bset = isl_basic_set_cow(bset);
		if (!bset)
			goto error;
		isl_basic_set_drop_inequality(bset, k);
		--k;
	}
	free(index);
	return bset;
error:
	free(index);
	return bset;
}
