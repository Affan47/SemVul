release_partition(WindowAggState *winstate)
{
	int			i;

	for (i = 0; i < winstate->numfuncs; i++)
	{
		WindowStatePerFunc perfuncstate = &(winstate->perfunc[i]);


		if (perfuncstate->winobj)
			perfuncstate->winobj->localmem = NULL;
	}


	MemoryContextResetAndDeleteChildren(winstate->partcontext);
	MemoryContextResetAndDeleteChildren(winstate->aggcontext);

	if (winstate->buffer)
		tuplestore_end(winstate->buffer);
	winstate->buffer = NULL;
	winstate->partition_spooled = false;
}
