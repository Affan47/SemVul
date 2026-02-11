seqoutUsaProcess(AjPSeqout thys)
{
    AjBool fmtstat;
    AjBool regstat;

#ifdef __CYGWIN__
    AjPStr usatmp = NULL;
#endif

    ajDebug("seqoutUsaProcess\n");
    if(!seqoutRegFmt)
#ifndef WIN32
	seqoutRegFmt = ajRegCompC("^([A-Za-z0-9-]*)::?(.*)$");


#else


    seqoutRegFmt = ajRegCompC("^([A-Za-z0-9][A-Za-z0-9-][A-Za-z0-9-]*)"
                              "::?(.*)$");


#endif


    if(!seqoutRegId)
	seqoutRegId = ajRegCompC("^(.*)$");

    ajStrAssignS(&seqoutUsaTest, thys->Usa);

#ifdef __CYGWIN__
    if(*(ajStrGetPtr(seqoutUsaTest)+1)==':')
    {
	usatmp = ajStrNew();
        ajFmtPrintS(&usatmp,"/cygdrive/%c/%s",*ajStrGetPtr(seqoutUsaTest),
		    ajStrGetPtr(seqoutUsaTest)+2);
        ajStrAssignRef(&seqoutUsaTest,usatmp);
        ajStrDel(&usatmp);
    }
#endif

    ajDebug("output USA to test: '%S'\n\n", seqoutUsaTest);

    fmtstat = ajRegExec(seqoutRegFmt, seqoutUsaTest);
    ajDebug("format regexp: %B\n", fmtstat);

    if(fmtstat)
    {
	ajRegSubI(seqoutRegFmt, 1, &thys->Formatstr);
	ajStrAssignEmptyC(&thys->Formatstr, seqOutFormat[0].Name);


	ajRegSubI(seqoutRegFmt, 2, &seqoutUsaTest);
	ajDebug("found format %S\n", thys->Formatstr);

	if(!seqoutFindOutFormat(thys->Formatstr, &thys->Format))
	{
	    ajDebug("unknown format '%S'\n", thys->Formatstr);

	    return ajFalse;
	}
    }
    else
	ajDebug("no format specified in USA\n");

    ajDebug("\n");

    regstat = ajRegExec(seqoutRegId, seqoutUsaTest);
    ajDebug("file:id regexp: %B\n", regstat);

    if(regstat)
    {
	ajRegSubI(seqoutRegId, 1, &thys->Filename);
	ajDebug("found filename %S single: %B dir: '%S'\n",
		thys->Filename, thys->Single, thys->Directory);

	if(thys->Single)
	    ajDebug("single output file per sequence, open later\n");
	else
	{
	    if(thys->Knownfile)
		thys->File = thys->Knownfile;
	    else
		thys->File = ajFileNewOutNamePathS(thys->Filename,
                                                   thys->Directory);

	    if(!thys->File)
	    {
		if(ajStrGetLen(thys->Directory))
		    ajErr("failed to open filename '%S' in directory '%S'",
			  thys->Filename, thys->Directory);
		else
		    ajErr("failed to open filename '%S'", thys->Filename);

		return ajFalse;
	    }
	}
    }
    else
	ajDebug("no filename specified\n");

    ajDebug("\n");

    return ajTrue;
}
