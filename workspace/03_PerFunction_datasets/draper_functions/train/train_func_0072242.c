Open( const char * pszFilename, int bUpdate )

{
    if( !EQUAL(CPLGetExtension(pszFilename), "pdf") || bUpdate )
        return NULL;


    OGRPDFDataSource     *poDS;

    poDS = new OGRPDFDataSource();

    if( !poDS->Open( pszFilename ) )
    {
        delete poDS;
        return NULL;
    }
    else
        return poDS;
}
