EPSGTreatsAsNorthingEasting()

{
    if( !IsProjected() )
        return FALSE;

    const char *pszAuth = GetAuthorityName( "PROJCS" );

    if( pszAuth == NULL || !EQUAL(pszAuth,"EPSG") )
        return FALSE;

    OGR_SRSNode *poFirstAxis = GetAttrNode( "PROJCS|AXIS" );

    if( poFirstAxis == NULL )
        return FALSE;

    if( poFirstAxis->GetChildCount() >= 2
        && EQUAL(poFirstAxis->GetChild(1)->GetValue(),"NORTH") )
        return TRUE;

    return FALSE;
}
