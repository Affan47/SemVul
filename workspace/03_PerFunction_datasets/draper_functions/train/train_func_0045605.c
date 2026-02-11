trans_binary_type(void)
{
	int index;
	int nparam = 0;

	if (PATTERN_is_class(*JOB->current))
	{
		index = CLASS_add_class(JOB->class, PATTERN_index(*JOB->current));
		if (PATTERN_is(JOB->current[1], RS_LSQR))
			index = CLASS_get_array_class(JOB->class, T_OBJECT, index);

		CODE_push_class(index);
	}
	else if (PATTERN_is_type(*JOB->current))
	{
		if (PATTERN_is(JOB->current[1], RS_LSQR))
		{
			index = CLASS_get_array_class(JOB->class, RES_get_type(PATTERN_index(*JOB->current)), -1);
			CODE_push_class(index);
		}
		else
		{
			index = RES_get_type(PATTERN_index(*JOB->current));
			CODE_push_number(index);
		}
	}
	else
		THROW(E_SYNTAX);

	JOB->current++;
	nparam++;

	#if 0
	if (TRANS_is(RS_LSQR))
	{
		TRANS_expression(FALSE);
		nparam++;
		TRANS_want(RS_RSQR, NULL);
	}
	else if (TRANS_is(RS_STAR))
	{
		if (!string)
			THROW("Syntax error");
		TRANS_expression(FALSE);
		nparam++;
	}
	#endif

	return nparam;
}
