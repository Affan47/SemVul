tsq_mcontains(PG_FUNCTION_ARGS)
{
	TSQuery		query = PG_GETARG_TSQUERY(0);
	TSQuery		ex = PG_GETARG_TSQUERY(1);
	TSQuerySign sq,
				se;
	int			i,
				j;
	QueryItem  *iq,
			   *ie;

	if (query->size < ex->size)
	{
		PG_FREE_IF_COPY(query, 0);
		PG_FREE_IF_COPY(ex, 1);

		PG_RETURN_BOOL(false);
	}

	sq = makeTSQuerySign(query);
	se = makeTSQuerySign(ex);

	if ((sq & se) != se)
	{
		PG_FREE_IF_COPY(query, 0);
		PG_FREE_IF_COPY(ex, 1);

		PG_RETURN_BOOL(false);
	}

	ie = GETQUERY(ex);

	for (i = 0; i < ex->size; i++)
	{
		iq = GETQUERY(query);
		if (ie[i].type != QI_VAL)
			continue;
		for (j = 0; j < query->size; j++)
			if (iq[j].type == QI_VAL && ie[i].operand.valcrc == iq[j].operand.valcrc)
			{
				j = query->size + 1;
				break;
			}
		if (j == query->size)
		{
			PG_FREE_IF_COPY(query, 0);
			PG_FREE_IF_COPY(ex, 1);

			PG_RETURN_BOOL(false);
		}
	}

	PG_FREE_IF_COPY(query, 0);
	PG_FREE_IF_COPY(ex, 1);

	PG_RETURN_BOOL(true);
}
