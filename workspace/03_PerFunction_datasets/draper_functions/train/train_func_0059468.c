ajAsseminDel(AjPAssemin* pthis)
{
    AjPAssemin thys;
    AjPSeqBamBgzf gzfile = NULL;

    if(!pthis)
        return;

    if(!*pthis)
        return;

    thys = *pthis;

    ajDebug("ajAsseminDel called qry:'%S'\n", thys->Input->Qry);

    if(thys->BamInput)
    {
        gzfile = thys->Input->TextData;
        ajSeqBamBgzfClose(gzfile);
    }

    ajTextinDel(&thys->Input);
    AJFREE(*pthis);

    return;
}
