TranslateProfileLine( NTFFileReader *poReader,
                                         OGRNTFLayer *poLayer,
                                         NTFRecord **papoGroup )

{
    if( CSLCount((char **) papoGroup) < 2
        || papoGroup[0]->GetType() != NRT_LINEREC
        || (papoGroup[1]->GetType() != NRT_GEOMETRY
            && papoGroup[1]->GetType() != NRT_GEOMETRY3D) )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( 0, atoi(papoGroup[0]->GetField( 3, 8 )) );


    poFeature->SetField( 1, papoGroup[0]->GetField( 17, 20 ) );


    poFeature->SetGeometryDirectly(poReader->ProcessGeometry(papoGroup[1]));


    poReader->ApplyAttributeValues( poFeature, papoGroup,
                                    "HT", 2,
                                    NULL );


    OGRLineString *poLine = (OGRLineString *) poFeature->GetGeometryRef();

    poFeature->SetField( 2, poFeature->GetFieldAsDouble(2) * 0.01 );
    if( poLine != NULL && poLine->getCoordinateDimension() == 2 )
    {
        for( int i = 0; i < poLine->getNumPoints(); i++ )
        {
            poLine->setPoint( i, poLine->getX(i), poLine->getY(i),
                              poFeature->GetFieldAsDouble(2) );
        }
    }
    else if( poLine != NULL )
    {
        double  dfAccum = 0.0;

        for( int i = 0; i < poLine->getNumPoints(); i++ )
        {
            dfAccum += poLine->getZ(i);
        }
        poFeature->SetField( 2, dfAccum / poLine->getNumPoints() );
    }

    return poFeature;
}
