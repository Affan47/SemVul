TParserClose(TParser *prs)
{
	while (prs->state)
	{
		TParserPosition *ptr = prs->state->prev;

		pfree(prs->state);
		prs->state = ptr;
	}

#ifdef USE_WIDE_UPPER_LOWER
	if (prs->wstr)
		pfree(prs->wstr);
	if (prs->pgwstr)
		pfree(prs->pgwstr);
#endif

	pfree(prs);
}
