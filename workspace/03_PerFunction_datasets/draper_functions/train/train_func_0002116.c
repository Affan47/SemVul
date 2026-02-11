CreateColorRamp(
            int nStartIndex, const GDALColorEntry *psStartColor,
            int nEndIndex, const GDALColorEntry *psEndColor )
{


    if( nStartIndex < 0 || nStartIndex > 255 ||
        nEndIndex < 0 || nEndIndex > 255 ||
        nStartIndex > nEndIndex )
    {
        return -1;
    }


    if( psStartColor == NULL || psEndColor == NULL )
    {
        return -1;
    }


    int nColors = nEndIndex - nStartIndex;


    SetColorEntry( nStartIndex, psStartColor );

    if( nColors == 0 )
    {
        return GetColorEntryCount();
    }


    SetColorEntry( nEndIndex, psEndColor );


    double dfSlope1, dfSlope2, dfSlope3, dfSlope4;

    dfSlope1 = ( psEndColor->c1 - psStartColor->c1 ) / (double) nColors;
    dfSlope2 = ( psEndColor->c2 - psStartColor->c2 ) / (double) nColors;
    dfSlope3 = ( psEndColor->c3 - psStartColor->c3 ) / (double) nColors;
    dfSlope4 = ( psEndColor->c4 - psStartColor->c4 ) / (double) nColors;


    GDALColorEntry sColor = *psStartColor;

    int i;

    for( i = 1; i < nColors; i++ )
    {
        sColor.c1 = (short) ( i * dfSlope1 + (double) psStartColor->c1 );
        sColor.c2 = (short) ( i * dfSlope2 + (double) psStartColor->c2 );
        sColor.c3 = (short) ( i * dfSlope3 + (double) psStartColor->c3 );
        sColor.c4 = (short) ( i * dfSlope4 + (double) psStartColor->c4 );

        SetColorEntry( nStartIndex + i, &sColor );
    }


    return GetColorEntryCount();
}
