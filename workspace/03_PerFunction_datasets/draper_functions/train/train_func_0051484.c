WriteDataChunksForTocEntry(ArchiveHandle *AH, DumpOptions *dopt, TocEntry *te)
{
	StartDataPtr startPtr;
	EndDataPtr	endPtr;

	AH->currToc = te;

	if (strcmp(te->desc, "BLOBS") == 0)
	{
		startPtr = AH->StartBlobsPtr;
		endPtr = AH->EndBlobsPtr;
	}
	else
	{
		startPtr = AH->StartDataPtr;
		endPtr = AH->EndDataPtr;
	}

	if (startPtr != NULL)
		(*startPtr) (AH, te);


	(*te->dataDumper) ((Archive *) AH, dopt, te->dataDumperArg);

	if (endPtr != NULL)
		(*endPtr) (AH, te);

	AH->currToc = NULL;
}
