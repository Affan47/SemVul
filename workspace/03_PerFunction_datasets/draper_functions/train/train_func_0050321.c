GetMetadata( const char *pszDomain )

{
    if( pszDomain != NULL && EQUAL(pszDomain,"SUBDATASETS") )
        return papszSubDatasets;

    return GDALPamDataset::GetMetadata( pszDomain );
}
