AddEdges( GInt32 *panThisLineId, GInt32 *panLastLineId,
                      GInt32 *panPolyIdMap, float *pafPolyValue,
                      RPolygonF **papoPoly, int iX, int iY )

{
    int nThisId = panThisLineId[iX];
    int nRightId = panThisLineId[iX+1];
    int nPreviousId = panLastLineId[iX];
    int iXReal = iX - 1;

    if( nThisId != -1 )
        nThisId = panPolyIdMap[nThisId];
    if( nRightId != -1 )
        nRightId = panPolyIdMap[nRightId];
    if( nPreviousId != -1 )
        nPreviousId = panPolyIdMap[nPreviousId];

    if( nThisId != nPreviousId )
    {
        if( nThisId != -1 )
        {
            if( papoPoly[nThisId] == NULL )
                papoPoly[nThisId] = new RPolygonF( pafPolyValue[nThisId] );

            papoPoly[nThisId]->AddSegment( iXReal, iY, iXReal+1, iY );
        }
        if( nPreviousId != -1 )
        {
            if( papoPoly[nPreviousId] == NULL )
                papoPoly[nPreviousId] = new RPolygonF(pafPolyValue[nPreviousId]);

            papoPoly[nPreviousId]->AddSegment( iXReal, iY, iXReal+1, iY );
        }
    }

    if( nThisId != nRightId )
    {
        if( nThisId != -1 )
        {
            if( papoPoly[nThisId] == NULL )
                papoPoly[nThisId] = new RPolygonF(pafPolyValue[nThisId]);

            papoPoly[nThisId]->AddSegment( iXReal+1, iY, iXReal+1, iY+1 );
        }

        if( nRightId != -1 )
        {
            if( papoPoly[nRightId] == NULL )
                papoPoly[nRightId] = new RPolygonF(pafPolyValue[nRightId]);

            papoPoly[nRightId]->AddSegment( iXReal+1, iY, iXReal+1, iY+1 );
        }
    }
}
