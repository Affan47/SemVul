Open( const char * pszFilename, int bUpdate )

{
    if (bUpdate)
    {
        return NULL;
    }

    OGRSVGDataSource   *poDS = new OGRSVGDataSource();

    if( !poDS->Open( pszFilename, bUpdate ) )
    {
        delete poDS;
        poDS = NULL;
    }

    return poDS;
}
