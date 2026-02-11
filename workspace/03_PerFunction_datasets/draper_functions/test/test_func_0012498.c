Fixup()

{


    const OGR_SRSNode *poCS = GetAttrNode( "PROJCS" );

    if( poCS == NULL )
        poCS = GetAttrNode( "LOCAL_CS" );

    if( poCS == NULL )
        poCS = GetAttrNode( "GEOCCS" );

    if( poCS != NULL && poCS->FindChild( "UNIT" ) == -1 )
        SetLinearUnits( SRS_UL_METER, 1.0 );


    poCS = GetAttrNode( "GEOGCS" );
    if( poCS != NULL && poCS->FindChild( "UNIT" ) == -1 )
        SetAngularUnits( SRS_UA_DEGREE, CPLAtof(SRS_UA_DEGREE_CONV) );

    return FixupOrdering();
}
