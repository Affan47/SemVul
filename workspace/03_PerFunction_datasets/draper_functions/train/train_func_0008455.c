reportWriteListFile(AjPReport thys,
				const AjPFeattable ftable, const AjPSeq seq)
{
    AjPFile outf;
    AjIList iterft     = NULL;
    AjPFeature feature = NULL;
    ajuint istart = 0;
    ajuint iend   = 0;
    ajuint i = 0;
    ajlong ipos;
    ajint jpos;
    AjPStr tmpstr = NULL;
    AjPStr tmpname = NULL;

    outf = thys->File;
    thys->Showusa = ajTrue;

    ajReportWriteHeader(thys, ftable, seq);

    iterft = ajListIterNewread(ftable->Features);

    while(!ajListIterDone(iterft))
    {
	feature = (AjPFeature)ajListIterGet(iterft);
	istart = feature->Start;
	iend = feature->End;
	i++;

	ajFmtPrintS(&tmpstr, "[");

	if(istart)
	    ajFmtPrintAppS(&tmpstr, "%d", istart);

	ajFmtPrintAppS(&tmpstr, ":");

	if(iend)
	    ajFmtPrintAppS(&tmpstr, "%d", iend);

	if(feature->Strand == '-')
	    ajFmtPrintAppS(&tmpstr, ":r");

	ajFmtPrintAppS(&tmpstr, "]");

	ajStrAssignS(&tmpname, ajSeqGetUsaS(seq));

	if(ajStrGetCharLast(tmpname) == ']')
        {
	    jpos = ajStrGetLen(tmpname);
	    ipos = ajStrFindlastC(tmpname, "[");
	    ajStrCutRange(&tmpname, ipos, jpos);
	}

	if(ajStrGetLen(tmpstr) > 3)
	    ajFmtPrintF(outf, "%S%S\n",
			tmpname, tmpstr);
	else
	    ajFmtPrintF(outf, "%S\n",
			tmpname);

	ajStrDelStatic(&tmpstr);
    }

    ajReportWriteTail(thys, ftable, seq);

    ajListIterDel(&iterft);
    ajStrDel(&tmpstr);
    ajStrDel(&tmpname);

    return;
}
