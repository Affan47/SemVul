merge_init_final(Operation *op, struct berval* init, struct berval* any,
	struct berval* final)
{
	struct berval* merged, *temp;
	int i, any_count, count;

	for (any_count=0; any && any[any_count].bv_val; any_count++)
		;

	count = any_count;

	if (init->bv_val)
		count++;
	if (final->bv_val)
		count++;

	merged = (struct berval*)op->o_tmpalloc( (count+1)*sizeof(struct berval),
		op->o_tmpmemctx );
	temp = merged;

	if (init->bv_val) {
		ber_dupbv_x( temp, init, op->o_tmpmemctx );
		temp++;
	}

	for (i=0; i<any_count; i++) {
		ber_dupbv_x( temp, any, op->o_tmpmemctx );
		temp++; any++;
	}

	if (final->bv_val){
		ber_dupbv_x( temp, final, op->o_tmpmemctx );
		temp++;
	}
	BER_BVZERO( temp );
	return merged;
}
