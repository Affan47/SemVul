FindName( const char *pszKey ) const

{
    if( !IsSorted() )
        return CSLFindName( papszList, pszKey );


    int iStart=0, iEnd=nCount-1;
    int nKeyLen = strlen(pszKey);

    while( iStart <= iEnd )
    {
        int iMiddle = (iEnd+iStart)/2;
        const char *pszMiddle = papszList[iMiddle];

        if (EQUALN(pszMiddle, pszKey, nKeyLen)
            && (pszMiddle[nKeyLen] == '=' || pszMiddle[nKeyLen] == ':') )
            return iMiddle;

        if( STRCASECMP(pszKey,pszMiddle) < 0 )
            iEnd = iMiddle-1;
        else
            iStart = iMiddle+1;
    }

    return -1;
}
