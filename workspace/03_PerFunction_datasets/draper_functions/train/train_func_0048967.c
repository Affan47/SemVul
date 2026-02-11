ClearFilters()

{


    if( poSrcLayer != NULL )
    {
        poSrcLayer->SetAttributeFilter( "" );
        poSrcLayer->SetSpatialFilter( NULL );
    }


    swq_select *psSelectInfo = (swq_select *) pSelectInfo;
    int iJoin;

    if( psSelectInfo != NULL )
    {
        for( iJoin = 0; iJoin < psSelectInfo->join_count; iJoin++ )
        {
            swq_join_def *psJoinInfo = psSelectInfo->join_defs + iJoin;
            OGRLayer *poJoinLayer =
                papoTableLayers[psJoinInfo->secondary_table];

            poJoinLayer->SetAttributeFilter( "" );
        }
    }


    if( psSelectInfo != NULL )
    {
        for( int iTable = 0; iTable < psSelectInfo->table_count; iTable++ )
        {
            OGRLayer* poLayer = papoTableLayers[iTable];
            poLayer->SetIgnoredFields(NULL);
        }
    }
}
