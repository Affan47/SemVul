_ArchiveEntry(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *tctx;
	char		fn[MAXPGPATH];

	tctx = (lclTocEntry *) calloc(1, sizeof(lclTocEntry));
	if (!tctx)
		die_horribly(AH, modulename, "out of memory\n");
	if (te->dataDumper)
	{
		snprintf(fn, MAXPGPATH, "%d.dat", te->dumpId);
		tctx->filename = strdup(fn);
	}
	else if (strcmp(te->desc, "BLOBS") == 0)
		tctx->filename = strdup("blobs.toc");
	else
		tctx->filename = NULL;

	te->formatData = (void *) tctx;
}
