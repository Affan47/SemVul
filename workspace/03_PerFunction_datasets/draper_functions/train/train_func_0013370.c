SortTocFromFile(Archive *AHX, RestoreOptions *ropt)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	FILE	   *fh;
	char		buf[1024];
	char	   *cmnt;
	char	   *endptr;
	DumpId		id;
	TocEntry   *te;
	TocEntry   *tePrev;


	ropt->idWanted = (bool *) malloc(sizeof(bool) * AH->maxDumpId);
	memset(ropt->idWanted, 0, sizeof(bool) * AH->maxDumpId);


	tePrev = AH->toc;


	fh = fopen(ropt->tocFile, PG_BINARY_R);
	if (!fh)
		die_horribly(AH, modulename, "could not open TOC file \"%s\": %s\n",
					 ropt->tocFile, strerror(errno));

	while (fgets(buf, sizeof(buf), fh) != NULL)
	{

		cmnt = strchr(buf, ';');
		if (cmnt != NULL)
			cmnt[0] = '\0';


		if (strspn(buf, " \t\r") == strlen(buf))
			continue;


		id = strtol(buf, &endptr, 10);
		if (endptr == buf || id <= 0 || id > AH->maxDumpId ||
			ropt->idWanted[id - 1])
		{
			write_msg(modulename, "WARNING: line ignored: %s\n", buf);
			continue;
		}


		te = getTocEntryByDumpId(AH, id);
		if (!te)
			die_horribly(AH, modulename, "could not find entry for ID %d\n",
						 id);

		ropt->idWanted[id - 1] = true;

		_moveAfter(AH, tePrev, te);
		tePrev = te;
	}

	if (fclose(fh) != 0)
		die_horribly(AH, modulename, "could not close TOC file: %s\n",
					 strerror(errno));
}
