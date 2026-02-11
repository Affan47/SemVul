RPCInverseTransformPoint( GDALRPCTransformInfo *psTransform,
                          double dfPixel, double dfLine, double dfHeight,
                          double *pdfLong, double *pdfLat )

{
    double dfResultX, dfResultY;
    int    iIter;
    GDALRPCInfo *psRPC = &(psTransform->sRPC);


    dfResultX = psTransform->adfPLToLatLongGeoTransform[0]
        + psTransform->adfPLToLatLongGeoTransform[1] * dfPixel
        + psTransform->adfPLToLatLongGeoTransform[2] * dfLine;

    dfResultY = psTransform->adfPLToLatLongGeoTransform[3]
        + psTransform->adfPLToLatLongGeoTransform[4] * dfPixel
        + psTransform->adfPLToLatLongGeoTransform[5] * dfLine;


    double dfPixelDeltaX=0.0, dfPixelDeltaY=0.0;

    for( iIter = 0; iIter < 10; iIter++ )
    {
        double dfBackPixel, dfBackLine;

        RPCTransformPoint( psRPC, dfResultX, dfResultY, dfHeight,
                           &dfBackPixel, &dfBackLine );

        dfPixelDeltaX = dfBackPixel - dfPixel;
        dfPixelDeltaY = dfBackLine - dfLine;

        dfResultX = dfResultX
            - dfPixelDeltaX * psTransform->adfPLToLatLongGeoTransform[1]
            - dfPixelDeltaY * psTransform->adfPLToLatLongGeoTransform[2];
        dfResultY = dfResultY
            - dfPixelDeltaX * psTransform->adfPLToLatLongGeoTransform[4]
            - dfPixelDeltaY * psTransform->adfPLToLatLongGeoTransform[5];

        if( ABS(dfPixelDeltaX) < psTransform->dfPixErrThreshold
            && ABS(dfPixelDeltaY) < psTransform->dfPixErrThreshold )
        {
            iIter = -1;

            break;
        }

    }

    if( iIter != -1 )
        CPLDebug( "RPC", "Iterations %d: Got: %g,%g  Offset=%g,%g",
                  iIter,
                  dfResultX, dfResultY,
                  dfPixelDeltaX, dfPixelDeltaY );

    *pdfLong = dfResultX;
    *pdfLat = dfResultY;
}
