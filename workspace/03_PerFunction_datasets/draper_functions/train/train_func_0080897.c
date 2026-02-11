lowerstr_with_len(const char *str, int len)
{
	char	   *out;

	if (len == 0)
		return pstrdup("");

#ifdef USE_WIDE_UPPER_LOWER


	if (pg_database_encoding_max_length() > 1 && !lc_ctype_is_c())
	{
		wchar_t    *wstr,
				   *wptr;
		int			wlen;


		wptr = wstr = (wchar_t *) palloc(sizeof(wchar_t) * (len + 1));

		wlen = char2wchar(wstr, len + 1, str, len);
		Assert(wlen <= len);

		while (*wptr)
		{
			*wptr = towlower((wint_t) *wptr);
			wptr++;
		}


		len = pg_database_encoding_max_length() * wlen + 1;
		out = (char *) palloc(len);

		wlen = wchar2char(out, wstr, len);

		pfree(wstr);

		if (wlen < 0)
			ereport(ERROR,
					(errcode(ERRCODE_CHARACTER_NOT_IN_REPERTOIRE),
			errmsg("conversion from wchar_t to server encoding failed: %m")));
		Assert(wlen < len);
	}
	else
#endif
	{
		const char *ptr = str;
		char	   *outptr;

		outptr = out = (char *) palloc(sizeof(char) * (len + 1));
		while ((ptr - str) < len && *ptr)
		{
			*outptr++ = tolower(TOUCHAR(ptr));
			ptr++;
		}
		*outptr = '\0';
	}

	return out;
}
