ReadFeature( int nFeatureId, OGRFeatureDefn *poTarget )

{
    OGRFeature  *poFeature;

    if( nFeatureId < 0 || nFeatureId >= oFE_Index.GetCount() )
        return NULL;

    poFeature = AssembleFeature( oFE_Index.GetByIndex(nFeatureId),
                                 poTarget );
    if( poFeature != NULL )
        poFeature->SetFID( nFeatureId );

    return poFeature;
}
