TRANS_output_to()
{
	TRANS_want(RS_TO, NULL);

	if (TRANS_is(RS_DEFAULT))
		CODE_push_null();
	else
		trans_stream(TS_NONE);

	trans_subr(TS_SUBR_OUTPUT_TO, 1);

	if (TRANS_in_affectation == 0)
		CODE_drop();
}
