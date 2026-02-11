GetMetadataItem( const char * pszName, const char * pszDomain )
{
    if (poOvrDS != NULL)
        return poOvrDS->GetMetadataItem(pszName, pszDomain);

    return poDS->GetMetadataItem(pszName, pszDomain);
}
