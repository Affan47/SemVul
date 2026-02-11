jaspextract_copyfiles(AjPStr directory)
{
    AjPStr matrixfile = NULL;
    AjPList flist     = NULL;

    AjPStr wild  = NULL;
    AjPStr entry = NULL;
    AjPStr bname = NULL;
    AjPStr line  = NULL;
    AjPStr dest  = NULL;

    const AjPStr datadir = NULL;

    ajuint preflen = 0;
    ajuint i       = 0;
    const char *p  = NULL;

    AjPFile inf   = NULL;
    AjPFile outf  = NULL;

    matrixfile = ajStrNew();
    flist      = ajListNew();
    wild       = ajStrNewC("*.pfm");
    bname      = ajStrNew();
    line       = ajStrNew();
    dest       = ajStrNew();


    datadir = ajDatafileValuePath();
    if(!datadir)
        ajFatal("jaspextract: Cannot determine the EMBOSS data directory");

    ajFmtPrintS(&matrixfile,"%S%s",directory,MATRIXFILE);

    if(!ajFilenameExistsRead(matrixfile))
        ajFatal("jaspextract: Directory (%S) doesn't appear to be a JASPAR "
                "one\nNo matrix_list.txt file found",directory);

    ajFilelistAddPathWild(flist, directory, wild);


    while(ajListPop(flist,(void **)&entry))
    {
        ajStrAssignS(&bname,entry);
        ajFilenameTrimPath(&bname);

        i = 0;

        while(Jprefix[i].Prefix)
        {
            if(!ajStrPrefixC(bname,Jprefix[i].Prefix))
            {
                ++i;
                continue;
            }

            preflen = strlen(Jprefix[i].Prefix);
            p = ajStrGetPtr(bname);
            if(p[preflen]>='0' && p[preflen]<='9')
                break;

            ++i;
        }

        if(!Jprefix[i].Prefix)
        {
            ajStrDel(&entry);
            continue;
        }


        ajFmtPrintS(&dest,"%S%s%c%S",datadir,Jprefix[i].Directory,SLASH_CHAR,
                    bname);

        outf = ajFileNewOutNameS(dest);
        if(!outf)
            ajFatal("Cannot open output file %S",dest);


        inf  = ajFileNewInNameS(entry);
        if(!inf)
            ajFatal("Cannot open input file: %S",entry);

        while(ajReadlineTrim(inf,&line))
            ajFmtPrintF(outf,"%S\n",line);

        ajFileClose(&inf);
        ajFileClose(&outf);

        ajStrDel(&entry);

    }

    ajListFree(&flist);

    ajStrDel(&wild);
    ajStrDel(&dest);
    ajStrDel(&line);
    ajStrDel(&bname);
    ajStrDel(&matrixfile);

    return;
}
