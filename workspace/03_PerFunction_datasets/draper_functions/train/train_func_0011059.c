TRANS_error(void)
{
	if (TRANS_is(RS_TO))
	{
		if (TRANS_is(RS_DEFAULT))
			CODE_push_null();
		else
			trans_stream(TS_NONE);

		trans_subr(TS_SUBR_ERROR_TO, 1);

		if (TRANS_in_affectation == 0)
			CODE_drop();
	}
	else
	{
		CODE_push_number(2);
		trans_print_debug();
	}
}
