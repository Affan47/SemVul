Identify( GDALOpenInfo * poOpenInfo )

{


    if( poOpenInfo->nHeaderBytes < 50 )
        return FALSE;


    if( (!EQUALN((char *)poOpenInfo->pabyHeader+11,"19",2)
          && !EQUALN((char *)poOpenInfo->pabyHeader+11,"20",2))
        || (!EQUALN((char *)poOpenInfo->pabyHeader+15,"19",2)
             && !EQUALN((char *)poOpenInfo->pabyHeader+15,"20",2))
        || (!EQUALN((char *)poOpenInfo->pabyHeader+19,"19",2)
             && !EQUALN((char *)poOpenInfo->pabyHeader+19,"20",2)) )
    {
        return FALSE;
    }

    return TRUE;
}
