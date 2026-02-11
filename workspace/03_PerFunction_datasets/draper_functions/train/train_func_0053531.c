_ReopenArchive(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	pgoff_t		tpos;

	if (AH->mode == archModeWrite)
		exit_horribly(modulename, "can only reopen input archives\n");


	if (AH->fSpec == NULL || strcmp(AH->fSpec, "") == 0)
		exit_horribly(modulename, "parallel restore from standard input is not supported\n");
	if (!ctx->hasSeek)
		exit_horribly(modulename, "parallel restore from non-seekable file is not supported\n");

	tpos = ftello(AH->FH);
	if (tpos < 0)
		exit_horribly(modulename, "could not determine seek position in archive file: %s\n",
					  strerror(errno));

#ifndef WIN32
	if (fclose(AH->FH) != 0)
		exit_horribly(modulename, "could not close archive file: %s\n",
					  strerror(errno));
#endif

	AH->FH = fopen(AH->fSpec, PG_BINARY_R);
	if (!AH->FH)
		exit_horribly(modulename, "could not open input file \"%s\": %s\n",
					  AH->fSpec, strerror(errno));

	if (fseeko(AH->FH, tpos, SEEK_SET) != 0)
		exit_horribly(modulename, "could not set seek position in archive file: %s\n",
					  strerror(errno));
}
