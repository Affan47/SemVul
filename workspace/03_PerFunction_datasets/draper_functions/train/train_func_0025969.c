add_stat(artifact_type *a_ptr)
{
	int r;
	bool success = FALSE;


	if (flags_test_all(a_ptr->flags, OF_SIZE, OF_STR, OF_INT, OF_WIS,
	                         OF_DEX, OF_CON, OF_CHR, FLAG_END))
			return;


	while (!success)
	{
		r = randint0(6);
		if (r == 0) success = add_fixed_pval_flag(a_ptr, OF_STR);
		else if (r == 1) success = add_fixed_pval_flag(a_ptr, OF_INT);
		else if (r == 2) success = add_fixed_pval_flag(a_ptr, OF_WIS);
		else if (r == 3) success = add_fixed_pval_flag(a_ptr, OF_DEX);
		else if (r == 4) success = add_fixed_pval_flag(a_ptr, OF_CON);
		else if (r == 5) success = add_fixed_pval_flag(a_ptr, OF_CHR);
	}
}
