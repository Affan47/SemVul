SetExtension( const char *pszTargetKey,
                                          const char *pszName,
                                          const char *pszValue )

{


    OGR_SRSNode  *poNode;

    if( pszTargetKey == NULL )
        poNode = poRoot;
    else
        poNode= ((OGRSpatialReference *) this)->GetAttrNode( pszTargetKey );

    if( poNode == NULL )
        return OGRERR_FAILURE;


    for( int i = poNode->GetChildCount()-1; i >= 0; i-- )
    {
        OGR_SRSNode *poChild = poNode->GetChild(i);

        if( EQUAL(poChild->GetValue(),"EXTENSION")
            && poChild->GetChildCount() >= 2 )
        {
            if( EQUAL(poChild->GetChild(0)->GetValue(),pszName) )
            {
                poChild->GetChild(1)->SetValue( pszValue );
                return OGRERR_NONE;
            }
        }
    }


    OGR_SRSNode *poAuthNode;

    poAuthNode = new OGR_SRSNode( "EXTENSION" );
    poAuthNode->AddChild( new OGR_SRSNode( pszName ) );
    poAuthNode->AddChild( new OGR_SRSNode( pszValue ) );

    poNode->AddChild( poAuthNode );

    return OGRERR_NONE;
}
