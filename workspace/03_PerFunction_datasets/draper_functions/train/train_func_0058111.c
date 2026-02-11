TranslateBL2000Link( NTFFileReader *poReader,
                                        OGRNTFLayer *poLayer,
                                        NTFRecord **papoGroup )

{
    if( CSLCount((char **) papoGroup) != 3
        || papoGroup[0]->GetType() != NRT_LINEREC
        || papoGroup[1]->GetType() != NRT_GEOMETRY
        || papoGroup[2]->GetType() != NRT_ATTREC )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


    int         nGeomId;

    poFeature->SetGeometryDirectly(poReader->ProcessGeometry(papoGroup[1],
                                                             &nGeomId));


    poFeature->SetField( 1, nGeomId );


    poReader->ApplyAttributeValues( poFeature, papoGroup,
                                    "FC", 2, "LK", 3,
                                    NULL );

    return poFeature;
}
