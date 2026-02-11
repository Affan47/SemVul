TranslateLandlineLine( NTFFileReader *poReader,
                                          OGRNTFLayer *poLayer,
                                          NTFRecord **papoGroup )

{
    if( CSLCount((char **) papoGroup) != 2
        || papoGroup[0]->GetType() != NRT_LINEREC
        || papoGroup[1]->GetType() != NRT_GEOMETRY )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


    poFeature->SetField( 1, papoGroup[0]->GetField( 17, 20 ) );


    poFeature->SetGeometryDirectly(poReader->ProcessGeometry(papoGroup[1]));


    if( poFeature->GetFieldIndex("CHG_DATE") == 2 )
    {
        poFeature->SetField( 2, papoGroup[0]->GetField( 23, 28 ) );
    }


    if( poFeature->GetFieldIndex("CHG_TYPE") == 3 )
    {
        poFeature->SetField( 3, papoGroup[0]->GetField( 22, 22 ) );
    }
    return poFeature;
}
