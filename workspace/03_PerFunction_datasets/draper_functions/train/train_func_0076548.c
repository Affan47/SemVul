TestCapability( const char* pszCap )

{
    if( EQUAL(pszCap,OLCRandomRead) )
        return FALSE;

    else if( EQUAL(pszCap,OLCSequentialWrite) )
        return TRUE;

    else if( EQUAL(pszCap,OLCRandomWrite) )
        return FALSE;

    else if( EQUAL(pszCap,OLCFastSpatialFilter) )
        return FALSE;

    else if( EQUAL(pszCap,OLCFastFeatureCount) )
        return FALSE;

    else if( EQUAL(pszCap,OLCFastGetExtent) )
        return FALSE;

    else if( EQUAL(pszCap,OLCFastSetNextByIndex) )
        return FALSE;

    else if( EQUAL(pszCap,OLCDeleteFeature) )
        return FALSE;

    else if( EQUAL(pszCap,OLCCreateField) )
        return TRUE;

    else
        return FALSE;
}
