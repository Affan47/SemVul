BuildArchiveDependencies(Archive *fout)
{
	ArchiveHandle *AH = (ArchiveHandle *) fout;
	TocEntry   *te;


	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		DumpableObject *dobj;
		DumpId	   *dependencies;
		int			nDeps;
		int			allocDeps;


		if (te->reqs == 0)
			continue;

		if (te->nDeps > 0)
			continue;

		dobj = findObjectByDumpId(te->dumpId);
		if (dobj == NULL)
			continue;

		if (dobj->nDeps <= 0)
			continue;

		allocDeps = 64;
		dependencies = (DumpId *) pg_malloc(allocDeps * sizeof(DumpId));
		nDeps = 0;

		findDumpableDependencies(AH, dobj,
								 &dependencies, &nDeps, &allocDeps);

		if (nDeps > 0)
		{
			dependencies = (DumpId *) pg_realloc(dependencies,
												 nDeps * sizeof(DumpId));
			te->dependencies = dependencies;
			te->nDeps = nDeps;
		}
		else
			free(dependencies);
	}
}
