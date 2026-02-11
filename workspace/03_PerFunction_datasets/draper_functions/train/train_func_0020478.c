_EndBlobs(ArchiveHandle *AH, TocEntry *te)
{
	lclContext *ctx = (lclContext *) AH->formatData;


	if (fclose(ctx->blobToc) != 0)
		die_horribly(AH, modulename, "could not close large object TOC file: %s\n", strerror(errno));
}
