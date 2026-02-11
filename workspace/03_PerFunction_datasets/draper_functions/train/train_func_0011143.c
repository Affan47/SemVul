trans_print_debug()
{
	int nparam = 1;
	bool semicolon_or_comma = FALSE;

	for(;;)
	{
		if (PATTERN_is_newline(*JOB->current))
			break;

		TRANS_expression(FALSE);
		nparam++;
		semicolon_or_comma = FALSE;

		if (PATTERN_is_newline(*JOB->current))
			break;

		if (TRANS_is(RS_SCOLON))
		{
			if (TRANS_is(RS_SCOLON))
			{
				CODE_push_char(' ');
				nparam++;
			}
			semicolon_or_comma = TRUE;
		}
		else if (TRANS_is(RS_COMMA))
		{
			CODE_push_char('\t');
			nparam++;
			semicolon_or_comma = TRUE;
		}
		else
			THROW(E_SYNTAX);
	}

	if (!semicolon_or_comma)
	{
		CODE_push_char('\n');
		nparam++;
	}

	trans_subr(TS_SUBR_PRINT, nparam);
	CODE_drop();
}
