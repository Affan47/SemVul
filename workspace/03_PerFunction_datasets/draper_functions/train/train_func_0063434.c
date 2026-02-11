header_extern(TRANS_EXTERN *trans)
{
	PATTERN *look = JOB->current;
	TRANS_DECL ttyp;
	int index;
	bool is_public;

	check_public_private(&look, &is_public);

	if (!PATTERN_is(*look, RS_EXTERN))
		return FALSE;
	look++;

	CLEAR(trans);

	JOB->current = look;
	analyze_function_desc((TRANS_FUNC *)trans, HF_NO_3PTS);

	if (PATTERN_is(*JOB->current, RS_AS))
	{
		if (!TRANS_type(TT_NOTHING, &ttyp))
			THROW("Syntax error in return type");
		trans->type = ttyp.type;
	}

	if (TRANS_is(RS_IN))
	{
		if (!PATTERN_is_string(*JOB->current))
			THROW("Library name must be a string");

		index = PATTERN_index(*JOB->current);
		JOB->current++;
	}
	else
	{
		if (JOB->default_library == NO_SYMBOL)
			THROW(E_MISSING, "IN");

		index = JOB->default_library;
	}

	trans->library = index;

	if (TRANS_is(RS_EXEC))
	{
		if (!PATTERN_is_string(*JOB->current))
			THROW("Alias name must be a string");

		trans->alias = PATTERN_index(*JOB->current);
		JOB->current++;
	}
	else
		trans->alias = NO_SYMBOL;

	TYPE_set_kind(&trans->type, TK_EXTERN);
	TYPE_set_flag(&trans->type, TF_STATIC);
	if (is_public) TYPE_set_flag(&trans->type, TF_PUBLIC);

	return TRUE;
}
