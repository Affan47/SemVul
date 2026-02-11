trans_exec_shell(bool shell)
{
	int mode = TS_EXEC_NONE;
	bool wait;
	bool as = TRUE;

	TRANS_expression(FALSE);

	if (TRANS_is(RS_WITH))
		TRANS_expression(FALSE);
	else
		CODE_push_null();

	wait = TRANS_is(RS_WAIT);

	if (TRANS_is(RS_FOR))
	{
		if (TRANS_is(RS_READ))
			mode |= TS_EXEC_READ;
		if (TRANS_is(RS_WRITE))
			mode |= TS_EXEC_WRITE;

		if (mode == 0)
		{
			mode |= TS_EXEC_TERM;
			if (TRANS_is(RS_INPUT))
				mode |= TS_EXEC_READ;
			if (TRANS_is(RS_OUTPUT))
				mode |= TS_EXEC_WRITE;
		}
	}
	else if (TRANS_is(RS_TO))
	{
		if (TRANS_in_affectation)
			THROW("Syntax error. Cannot use this syntax in assignment");

		mode = TS_EXEC_STRING;
		wait = TRUE;
		as = FALSE;
	}

	if (wait) mode |= TS_EXEC_WAIT;
	CODE_push_number(mode);

	if (as && TRANS_is(RS_AS))
		TRANS_expression(FALSE);
	else
		CODE_push_null();

	trans_subr(shell ? TS_SUBR_SHELL : TS_SUBR_EXEC, 4);

	if (mode & TS_EXEC_STRING)
		TRANS_reference();
	else if (TRANS_in_affectation == 0)
		CODE_drop();
}
