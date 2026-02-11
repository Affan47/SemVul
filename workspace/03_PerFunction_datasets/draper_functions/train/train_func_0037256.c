EjectContours( int bOnlyUnused )

{
    int iLevel;
    CPLErr eErr = CE_None;


    for( iLevel = 0; iLevel < nLevelCount && eErr == CE_None; iLevel++ )
    {
        GDALContourLevel *poLevel = papoLevels[iLevel];
        int iContour;

        for( iContour = 0;
             iContour < poLevel->GetContourCount() && eErr == CE_None;
              )
        {
            int  iC2;
            GDALContourItem *poTarget = poLevel->GetContour( iContour );

            if( bOnlyUnused && poTarget->bRecentlyAccessed )
            {
                iContour++;
                continue;
            }

            poLevel->RemoveContour( iContour );


            for( iC2 = 0; iC2 < poLevel->GetContourCount(); iC2++ )
            {
                GDALContourItem *poOther = poLevel->GetContour( iC2 );

                if( poOther->Merge( poTarget ) )
                    break;
            }


            if( iC2 == poLevel->GetContourCount() )
            {
                if( pfnWriter != NULL )
                {

                    poTarget->PrepareEjection();

                    eErr = pfnWriter( poTarget->dfLevel, poTarget->nPoints,
                                      poTarget->padfX, poTarget->padfY,
                                      pWriterCBData );
                }
            }

            delete poTarget;
        }
    }

    return eErr;
}
