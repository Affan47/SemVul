TwoPhaseShmemInit(void)
{
	bool		found;

	TwoPhaseState = ShmemInitStruct("Prepared Transaction Table",
									TwoPhaseShmemSize(),
									&found);
	if (!IsUnderPostmaster)
	{
		GlobalTransaction gxacts;
		int			i;

		Assert(!found);
		TwoPhaseState->freeGXacts = NULL;
		TwoPhaseState->numPrepXacts = 0;


		gxacts = (GlobalTransaction)
			((char *) TwoPhaseState +
			 MAXALIGN(offsetof(TwoPhaseStateData, prepXacts) +
					  sizeof(GlobalTransaction) * max_prepared_xacts));
		for (i = 0; i < max_prepared_xacts; i++)
		{
			gxacts[i].proc.links.next = (SHM_QUEUE *) TwoPhaseState->freeGXacts;
			TwoPhaseState->freeGXacts = &gxacts[i];


			gxacts[i].dummyBackendId = MaxBackends + 1 + i;
		}
	}
	else
		Assert(found);
}
