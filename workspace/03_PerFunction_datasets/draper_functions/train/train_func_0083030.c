TestCapability (
    const char *pszCap )
{
    int result = FALSE;

    if ( EQUAL ( pszCap, OLCRandomRead ) )
        result = FALSE;
    else if ( EQUAL ( pszCap, OLCSequentialWrite ) )
        result = bUpdate;
    else if ( EQUAL ( pszCap, OLCRandomWrite ) )
        result = FALSE;
    else if ( EQUAL ( pszCap, OLCFastFeatureCount ) )
        result = FALSE;
    else if ( EQUAL ( pszCap, OLCFastSetNextByIndex ) )
        result = FALSE;
    else if ( EQUAL ( pszCap, OLCCreateField ) )
        result = bUpdate;
    else if ( EQUAL ( pszCap, OLCDeleteFeature ) )
        result = FALSE;
    else if ( EQUAL(pszCap, OLCStringsAsUTF8) )
        result = TRUE;

    return result;
}
