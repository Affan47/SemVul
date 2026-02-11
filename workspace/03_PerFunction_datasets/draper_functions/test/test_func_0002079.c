TranslateGenericPoly( NTFFileReader *poReader,
                                         OGRNTFLayer *poLayer,
                                         NTFRecord **papoGroup )

{


    if( CSLCount((char **) papoGroup) >= 2
        && papoGroup[0]->GetType() == NRT_POLYGON
        && papoGroup[1]->GetType() == NRT_CHAIN )
    {
        OGRFeature      *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


        poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


        int             nNumLinks = atoi(papoGroup[1]->GetField( 9, 12 ));

        if( nNumLinks > MAX_LINK )
        {
            CPLError( CE_Failure, CPLE_AppDefined,
                      "MAX_LINK exceeded in ntf_generic.cpp." );
            return poFeature;
        }

        poFeature->SetField( "NUM_PARTS", nNumLinks );


        int             i, anList[MAX_LINK];

        for( i = 0; i < nNumLinks; i++ )
            anList[i] = atoi(papoGroup[1]->GetField( 19+i*7, 19+i*7 ));

        poFeature->SetField( "DIR", nNumLinks, anList );


        for( i = 0; i < nNumLinks; i++ )
            anList[i] = atoi(papoGroup[1]->GetField( 13+i*7, 18+i*7 ));

        poFeature->SetField( "GEOM_ID_OF_LINK", nNumLinks, anList );


        int     nRingList = 0;
        poFeature->SetField( "RingStart", 1, &nRingList );


        AddGenericAttributes( poReader, papoGroup, poFeature );


        if( papoGroup[2] != NULL
            && (papoGroup[2]->GetType() == NRT_GEOMETRY
                || papoGroup[2]->GetType() == NRT_GEOMETRY3D) )
        {
            poFeature->SetGeometryDirectly(
                poReader->ProcessGeometry(papoGroup[2]));
            poFeature->SetField( "GEOM_ID", papoGroup[2]->GetField(3,8) );
        }

        return poFeature;
    }

    return NULL;
}
