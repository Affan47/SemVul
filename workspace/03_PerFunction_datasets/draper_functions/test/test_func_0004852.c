relocate_data()
{
	CELL relocating;

	CELL i;
	for(i = 0; i < USER_ENV; i++)
		data_fixup(&userenv[i]);

	data_fixup(&T);
	data_fixup(&bignum_zero);
	data_fixup(&bignum_pos_one);
	data_fixup(&bignum_neg_one);

	F_ZONE *tenured = &data_heap->generations[TENURED];

	for(relocating = tenured->start;
		relocating < tenured->here;
		relocating += untagged_object_size(relocating))
	{
		allot_barrier(relocating);
		relocate_object(relocating);
	}
}
