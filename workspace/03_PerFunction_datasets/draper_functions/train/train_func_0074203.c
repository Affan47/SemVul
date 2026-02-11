Identify( GDALOpenInfo * poOpenInfo )

{
    const char *pszFilename = poOpenInfo->pszFilename;


    if( EQUALN(pszFilename, "NITF_IM:",8) )
        return TRUE;


    if( EQUALN(pszFilename,"JPEG_SUBFILE:",13) )
        return FALSE;


    if( poOpenInfo->nHeaderBytes < 4 )
        return FALSE;

    if( !EQUALN((char *) poOpenInfo->pabyHeader,"NITF",4)
        && !EQUALN((char *) poOpenInfo->pabyHeader,"NSIF",4)
        && !EQUALN((char *) poOpenInfo->pabyHeader,"NITF",4) )
        return FALSE;

    int i;

    for(i=0;i<(int)poOpenInfo->nHeaderBytes-(int)strlen("A.TOC");i++)
    {
        if (EQUALN((const char*)poOpenInfo->pabyHeader + i, "A.TOC", strlen("A.TOC")))
            return FALSE;
    }

    return TRUE;
}
