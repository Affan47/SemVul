add_operator_output(short op, short nparam, uint64_t byref)
{
	PATTERN pattern;


	if (op == RS_NONE || op == RS_UNARY)
		return;

	if (op == RS_EXCL)
	{
		op = RS_LSQR;
		nparam = 2;

		check_last_first(2);
	}

	pattern = PATTERN_make(RT_RESERVED, op);


	add_pattern(pattern);

	add_pattern(PATTERN_make(RT_PARAM, nparam));

	if (op == RS_LBRA && byref)
	{
		while (byref)
		{
			add_pattern(PATTERN_make(RT_PARAM, byref & 0xFFFF));
			byref >>= 16;
		}
	}
}
