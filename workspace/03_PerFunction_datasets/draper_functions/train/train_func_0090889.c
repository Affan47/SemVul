S57GenerateObjectClassDefn( S57ClassRegistrar *poCR,
                                            int nOBJL, int nOptionFlags )

{
    OGRFeatureDefn      *poFDefn = NULL;
    char               **papszGeomPrim;

    if( !poCR->SelectClass( nOBJL ) )
        return NULL;


    poFDefn = new OGRFeatureDefn( poCR->GetAcronym() );
    poFDefn->Reference();


    papszGeomPrim = poCR->GetPrimitives();
    if( CSLCount(papszGeomPrim) == 0 )
    {
        poFDefn->SetGeomType( wkbNone );
    }
    else if( CSLCount(papszGeomPrim) > 1 )
    {

    }
    else if( papszGeomPrim[0][0] == 'P' )
    {
        if( EQUAL(poCR->GetAcronym(),"SOUNDG") )
        {
            if( nOptionFlags & S57M_SPLIT_MULTIPOINT )
                poFDefn->SetGeomType( wkbPoint25D );
            else
                poFDefn->SetGeomType( wkbMultiPoint25D );
        }
        else
            poFDefn->SetGeomType( wkbPoint );
    }
    else if( papszGeomPrim[0][0] == 'A' )
    {
        poFDefn->SetGeomType( wkbPolygon );
    }
    else if( papszGeomPrim[0][0] == 'L' )
    {

        poFDefn->SetGeomType( wkbUnknown );
    }


    S57GenerateStandardAttributes( poFDefn, nOptionFlags );


    char        **papszAttrList = poCR->GetAttributeList();

    for( int iAttr = 0;
         papszAttrList != NULL && papszAttrList[iAttr] != NULL;
         iAttr++ )
    {
        int     iAttrIndex = poCR->FindAttrByAcronym( papszAttrList[iAttr] );

        if( iAttrIndex == -1 )
        {
            CPLDebug( "S57", "Can't find attribute %s from class %s:%s.",
                      papszAttrList[iAttr],
                      poCR->GetAcronym(),
                      poCR->GetDescription() );
            continue;
        }

        OGRFieldDefn    oField( papszAttrList[iAttr], OFTInteger );

        switch( poCR->GetAttrType( iAttrIndex ) )
        {
          case SAT_ENUM:
          case SAT_INT:
            oField.SetType( OFTInteger );
            break;

          case SAT_FLOAT:
            oField.SetType( OFTReal );
            break;

          case SAT_CODE_STRING:
          case SAT_FREE_TEXT:
            oField.SetType( OFTString );
            break;

          case SAT_LIST:
            oField.SetType( OFTString );
            break;
        }

        poFDefn->AddFieldDefn( &oField );
    }


    if( EQUAL(poCR->GetAcronym(),"SOUNDG")
        && (nOptionFlags & S57M_ADD_SOUNDG_DEPTH) )
    {
        OGRFieldDefn    oField( "DEPTH", OFTReal );
        poFDefn->AddFieldDefn( &oField );
    }

    return poFDefn;
}
