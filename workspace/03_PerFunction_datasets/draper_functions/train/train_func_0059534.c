_EndBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;

	if (GZCLOSE(tctx->FH) != 0)
		die_horribly(AH, modulename, "could not close large object file\n");
}
