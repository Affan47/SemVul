MatchBytea(char *t, int tlen, char *p, int plen)
{

	if ((plen == 1) && (*p == '%'))
		return LIKE_TRUE;

	while ((tlen > 0) && (plen > 0))
	{
		if (*p == '\\')
		{

			BYTEA_NextChar(p, plen);
			if ((plen <= 0) || !BYTEA_CHAREQ(t, p))
				return LIKE_FALSE;
		}
		else if (*p == '%')
		{


			while ((plen > 0) && (*p == '%'))
				BYTEA_NextChar(p, plen);

			if (plen <= 0)
				return LIKE_TRUE;


			while (tlen > 0)
			{


				if (BYTEA_CHAREQ(t, p) || (*p == '\\') || (*p == '_'))
				{
					int			matched = MatchBytea(t, tlen, p, plen);

					if (matched != LIKE_FALSE)
						return matched;
				}

				BYTEA_NextChar(t, tlen);
			}


			return LIKE_ABORT;
		}
		else if ((*p != '_') && !BYTEA_CHAREQ(t, p))
		{


			return LIKE_FALSE;
		}

		BYTEA_NextChar(t, tlen);
		BYTEA_NextChar(p, plen);
	}

	if (tlen > 0)
		return LIKE_FALSE;


	while ((plen > 0) && (*p == '%'))

		BYTEA_NextChar(p, plen);
	if (plen <= 0)
		return LIKE_TRUE;


	return LIKE_ABORT;
}
