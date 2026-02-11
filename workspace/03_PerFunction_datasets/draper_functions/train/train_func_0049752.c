solve_recurse(struct solver_context *ctx, int branch_diff)
{
	cdok_pos_t cell;
	cdok_set_t candidates;
	int i;
	int diff;

	cell = find_candidates(ctx->puzzle, ctx->values, &candidates);


	if (cell < 0) {
		if (!ctx->count) {
			if (ctx->solution)
				memcpy(ctx->solution, ctx->values,
				       sizeof(ctx->values));
			ctx->branch_diff = branch_diff;
		}

		ctx->count++;
		return;
	}


	if (!candidates)
		return;


	diff = count_bits(candidates) - 1;
	diff = branch_diff + (diff * diff);

	for (i = 1; i <= ctx->puzzle->size; i++) {
		if (!(candidates & CDOK_SET_SINGLE(i)))
			continue;

		ctx->values[cell] = i;
		solve_recurse(ctx, diff);
		ctx->values[cell] = 0;

		if (ctx->count >= 2)
			return;
	}
}
