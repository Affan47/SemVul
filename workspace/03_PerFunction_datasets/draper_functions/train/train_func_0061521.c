NCDFDoesVarContainAttribVal( int nCdfId,
                                 const char ** papszAttribNames,
                                 const char ** papszAttribValues,
                                 int nVarId,
                                 const char * pszVarName,
                                 int bStrict=TRUE )
{
    char *pszTemp = NULL;
    int bFound = FALSE;

    if ( (nVarId == -1) && (pszVarName != NULL) )
        nc_inq_varid( nCdfId, pszVarName, &nVarId );

    if ( nVarId == -1 ) return -1;

    for( int i=0; !bFound && i<CSLCount((char**)papszAttribNames); i++ ) {
        if ( NCDFGetAttr( nCdfId, nVarId, papszAttribNames[i], &pszTemp )
             == CE_None ) {
            if ( bStrict ) {
                if ( EQUAL( pszTemp, papszAttribValues[i] ) )
                    bFound=TRUE;
            }
            else {
                if ( EQUALN( pszTemp, papszAttribValues[i], strlen(papszAttribValues[i]) ) )
                    bFound=TRUE;
            }
            CPLFree( pszTemp );
        }
    }
    return bFound;
}
