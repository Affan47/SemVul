GetMetadata( const char *pszDomain )

{
    if( pszDomain && EQUAL(pszDomain,"xml:dimap") )
    {
        if (papszXMLDimapMetadata == NULL)
        {
            papszXMLDimapMetadata = (char **) CPLCalloc(sizeof(char*),2);
            papszXMLDimapMetadata[0] = CPLSerializeXMLTree( psProduct );
        }
        return papszXMLDimapMetadata;
    }
    else
        return GDALPamDataset::GetMetadata( pszDomain );
}
