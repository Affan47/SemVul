RelationParseRelOptions(Relation relation, HeapTuple tuple)
{
	bytea	   *options;

	relation->rd_options = NULL;


	switch (relation->rd_rel->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_TOASTVALUE:
		case RELKIND_INDEX:
		case RELKIND_VIEW:
		case RELKIND_MATVIEW:
			break;
		default:
			return;
	}


	options = extractRelOptions(tuple,
								GetPgClassDescriptor(),
								relation->rd_rel->relkind == RELKIND_INDEX ?
								relation->rd_am->amoptions : InvalidOid);


	if (options)
	{
		relation->rd_options = MemoryContextAlloc(CacheMemoryContext,
												  VARSIZE(options));
		memcpy(relation->rd_options, options, VARSIZE(options));
		pfree(options);
	}
}
