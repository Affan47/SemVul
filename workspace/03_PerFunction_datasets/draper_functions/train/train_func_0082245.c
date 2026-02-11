lower(PG_FUNCTION_ARGS)
{
#ifdef USE_WIDE_UPPER_LOWER


	if (pg_database_encoding_max_length() > 1 && !lc_ctype_is_c())
	{
		text	   *string = PG_GETARG_TEXT_PP(0);
		text	   *result;
		wchar_t    *workspace;
		int			i;

		workspace = texttowcs(string);

		for (i = 0; workspace[i] != 0; i++)
			workspace[i] = towlower(workspace[i]);

		result = wcstotext(workspace, i);

		pfree(workspace);

		PG_RETURN_TEXT_P(result);
	}
	else
#endif
	{
		text	   *string = PG_GETARG_TEXT_P_COPY(0);
		char	   *ptr;
		int			m;


		ptr = VARDATA(string);
		m = VARSIZE(string) - VARHDRSZ;

		while (m-- > 0)
		{
			*ptr = tolower((unsigned char) *ptr);
			ptr++;
		}

		PG_RETURN_TEXT_P(string);
	}
}
