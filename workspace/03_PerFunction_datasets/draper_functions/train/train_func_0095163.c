more_tabstat_space(TabStatArray *tsarr)
{
	PgStat_MsgTabstat *newMessages;
	PgStat_MsgTabstat **msgArray;
	int			newAlloc;
	int			i;

	AssertArg(PointerIsValid(tsarr));

	newAlloc = tsarr->tsa_alloc + TABSTAT_QUANTUM;


	newMessages = (PgStat_MsgTabstat *)
		MemoryContextAllocZero(TopMemoryContext,
							   sizeof(PgStat_MsgTabstat) * TABSTAT_QUANTUM);


	if (tsarr->tsa_messages == NULL)
		msgArray = (PgStat_MsgTabstat **)
			MemoryContextAlloc(TopMemoryContext,
							   sizeof(PgStat_MsgTabstat *) * newAlloc);
	else
		msgArray = (PgStat_MsgTabstat **)
			repalloc(tsarr->tsa_messages,
					 sizeof(PgStat_MsgTabstat *) * newAlloc);

	for (i = 0; i < TABSTAT_QUANTUM; i++)
		msgArray[tsarr->tsa_alloc + i] = newMessages++;
	tsarr->tsa_messages = msgArray;
	tsarr->tsa_alloc = newAlloc;

	Assert(tsarr->tsa_used < tsarr->tsa_alloc);
}
