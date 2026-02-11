text_position_setup(text *t1, text *t2, TextPositionState *state)
{
	int			len1 = VARSIZE(t1) - VARHDRSZ;
	int			len2 = VARSIZE(t2) - VARHDRSZ;

	if (pg_database_encoding_max_length() == 1)
	{

		state->use_wchar = false;
		state->str1 = VARDATA(t1);
		state->str2 = VARDATA(t2);
		state->len1 = len1;
		state->len2 = len2;
	}
	else
	{

		pg_wchar   *p1,
				   *p2;

		p1 = (pg_wchar *) palloc((len1 + 1) * sizeof(pg_wchar));
		len1 = pg_mb2wchar_with_len(VARDATA(t1), p1, len1);
		p2 = (pg_wchar *) palloc((len2 + 1) * sizeof(pg_wchar));
		len2 = pg_mb2wchar_with_len(VARDATA(t2), p2, len2);

		state->use_wchar = true;
		state->wstr1 = p1;
		state->wstr2 = p2;
		state->len1 = len1;
		state->len2 = len2;
	}
}
