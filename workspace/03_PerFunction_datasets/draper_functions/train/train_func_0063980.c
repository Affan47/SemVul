TranslateAddressPoint( NTFFileReader *poReader,
                                          OGRNTFLayer *poLayer,
                                          NTFRecord **papoGroup )

{
    if( CSLCount((char **) papoGroup) < 2
        || papoGroup[0]->GetType() != NRT_POINTREC
        || papoGroup[1]->GetType() != NRT_GEOMETRY )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


    poFeature->SetField( 17, papoGroup[0]->GetField( 22, 22 ) );


    poFeature->SetField( 18, papoGroup[0]->GetField( 23, 28 ) );


    poFeature->SetGeometryDirectly(poReader->ProcessGeometry(papoGroup[1]));


    poReader->ApplyAttributeValues( poFeature, papoGroup,
                                    "OA", 1, "ON", 2, "DP", 3, "PB", 4,
                                    "SB", 5, "BD", 6, "BN", 7, "DR", 8,
                                    "TN", 9, "DD", 10, "DL", 11, "PT", 12,
                                    "CN", 13, "PC", 14, "SF", 15, "RV", 16,
                                    NULL );

    return poFeature;
}
