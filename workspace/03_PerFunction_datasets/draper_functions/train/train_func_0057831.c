AddSegment( double dfLevel,
                                         double dfX1, double dfY1,
                                         double dfX2, double dfY2,
                                         int bLeftHigh)

{
    GDALContourLevel *poLevel = FindLevel( dfLevel );
    GDALContourItem *poTarget;
    int iTarget;


    if( dfY1 < dfY2 )
        iTarget = poLevel->FindContour( dfX1, dfY1 );
    else
        iTarget = poLevel->FindContour( dfX2, dfY2 );

    if( iTarget != -1 )
    {
        poTarget = poLevel->GetContour( iTarget );

        poTarget->AddSegment( dfX1, dfY1, dfX2, dfY2, bLeftHigh );

        poLevel->AdjustContour( iTarget );

        return CE_None;
    }


    poTarget = new GDALContourItem( dfLevel );

    poTarget->AddSegment( dfX1, dfY1, dfX2, dfY2, bLeftHigh );

    poLevel->InsertContour( poTarget );

    return CE_None;
}
