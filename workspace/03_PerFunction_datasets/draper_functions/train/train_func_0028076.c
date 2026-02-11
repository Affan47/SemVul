TRANS_lock(void)
{
	if (PATTERN_is_newline(*JOB->current))
		THROW(E_SYNTAX);

	if (!TRANS_in_affectation)
		THROW("Useless LOCK");

	TRANS_expression(FALSE);

	trans_subr(TS_SUBR_LOCK, 1);
}
