TranslateOscarRoutePoint( NTFFileReader *poReader,
                                             OGRNTFLayer *poLayer,
                                             NTFRecord **papoGroup )

{
    if( CSLCount((char **) papoGroup) < 2
        || papoGroup[0]->GetType() != NRT_POINTREC
        || papoGroup[1]->GetType() != NRT_GEOMETRY )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


    int         nGeomId;

    poFeature->SetGeometryDirectly(poReader->ProcessGeometry(papoGroup[1],
                                                             &nGeomId));

    poFeature->SetField( 1, nGeomId );


    poReader->ApplyAttributeValues( poFeature, papoGroup,
                                    "FC", 2, "OD", 3, "JN", 4, "SN", 5,
                                    "NP", 6, "RT", 8,
                                    NULL );


    char        **papszTypes, **papszValues;

    if( poReader->ProcessAttRecGroup( papoGroup, &papszTypes, &papszValues ) )
    {
        char    **papszOSODRList = NULL;

        for( int i = 0; papszTypes != NULL && papszTypes[i] != NULL; i++ )
        {
            if( EQUAL(papszTypes[i],"PO") )
                papszOSODRList = CSLAddString(papszOSODRList,papszValues[i]);
        }

        poFeature->SetField( 7, papszOSODRList );
        CPLAssert( CSLCount(papszOSODRList) ==
                   poFeature->GetFieldAsInteger( 6 ) );

        CSLDestroy( papszOSODRList );
        CSLDestroy( papszTypes );
        CSLDestroy( papszValues );
    }

    return poFeature;
}
