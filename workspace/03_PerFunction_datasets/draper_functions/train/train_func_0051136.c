GetExtent(OGREnvelope *psExtent, int bForce )

{
    double dfXMin, dfXMax, dfYMin, dfYMax;

    if( poFClass != NULL &&
        poFClass->GetExtents( &dfXMin, &dfXMax, &dfYMin, &dfYMax ) )
    {
        psExtent->MinX = dfXMin;
        psExtent->MaxX = dfXMax;
        psExtent->MinY = dfYMin;
        psExtent->MaxY = dfYMax;

        return OGRERR_NONE;
    }
    else
        return OGRLayer::GetExtent( psExtent, bForce );
}
