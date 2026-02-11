embDbiSortWriteEntry(AjPFile entFile, ajuint maxidlen,
                            const AjPStr dbname, ajuint nfiles,
                            AjBool cleanup, const AjPStr sortopt)
{
    AjPFile esortfile;
    ajint rpos;
    ajint spos;
    ajint filenum;
    ajuint idcnt = 0;

    if(!dbiRegEntryIdSort)
	dbiRegEntryIdSort =
	    ajRegCompC("^([^ ]+) +([0-9]+) +([0-9]+) +([0-9]+)");

    embDbiSortFile(dbname, "list", "idsrt", nfiles, cleanup, sortopt);
    ajStrAssignC(&dbiLastId, " ");
    esortfile = embDbiFileIn(dbname, "idsrt");

    while(ajReadline(esortfile, &dbiRdLine))
    {
	ajRegExec(dbiRegEntryIdSort, dbiRdLine);
	ajRegSubI(dbiRegEntryIdSort, 1, &dbiIdStr);
	ajRegSubI(dbiRegEntryIdSort, 2, &dbiTmpStr);
	ajStrToInt(dbiTmpStr, &rpos);
	ajRegSubI(dbiRegEntryIdSort, 3, &dbiTmpStr);
	ajStrToInt(dbiTmpStr, &spos);
	ajRegSubI(dbiRegEntryIdSort, 4, &dbiTmpStr);
	ajStrToInt(dbiTmpStr, &filenum);

	if(ajStrMatchCaseS(dbiIdStr, dbiLastId))
	{
            ajDebug("Duplicate ID '%S' filenum: %d",
                    dbiIdStr, filenum);
            ajWarn("Duplicate ID skipped: '%S' "
                   "All hits will point to first ID found",
                   dbiIdStr);
            continue;
	}

	embDbiWriteEntryRecord(entFile, maxidlen, dbiIdStr,
			       rpos, spos, filenum);
	ajStrAssignS(&dbiLastId, dbiIdStr);
	idcnt++;
    }
    ajFileClose(&esortfile);

    return idcnt;
}
