SetMetadata( char **papszMetadata,
                                             const char *pszDomain )

{
    if( pszDomain == NULL )
        pszDomain = "";

    int iDomain = CSLFindString( papszDomainList, pszDomain );

    if( iDomain == -1 )
    {
        int nDomainCount;

        papszDomainList = CSLAddString( papszDomainList, pszDomain );
        nDomainCount = CSLCount( papszDomainList );

        papoMetadataLists = (CPLStringList **)
            CPLRealloc( papoMetadataLists, sizeof(void*)*(nDomainCount+1) );
        papoMetadataLists[nDomainCount] = NULL;
        papoMetadataLists[nDomainCount-1] = new CPLStringList();
        iDomain = nDomainCount-1;
    }

    papoMetadataLists[iDomain]->Assign( CSLDuplicate( papszMetadata ) );


    if( !EQUALN(pszDomain,"xml:",4) && !EQUAL(pszDomain, "SUBDATASETS") )
        papoMetadataLists[iDomain]->Sort();

    return CE_None;
}
