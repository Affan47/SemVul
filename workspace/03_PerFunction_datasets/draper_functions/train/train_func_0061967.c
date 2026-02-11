newTParserPosition(TParserPosition *prev)
{
	TParserPosition *res = (TParserPosition *) palloc(sizeof(TParserPosition));

	if (prev)
		memcpy(res, prev, sizeof(TParserPosition));
	else
		memset(res, 0, sizeof(TParserPosition));

	res->prev = prev;

	res->pushedAtAction = NULL;

	return res;
}
