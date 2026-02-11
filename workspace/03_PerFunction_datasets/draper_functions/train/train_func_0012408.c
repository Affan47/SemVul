GTIFDecToDMS( double dfAngle, const char * pszAxis,
                          int nPrecision )

{
    int		nDegrees, nMinutes;
    double	dfSeconds;
    char	szFormat[30];
    static char szBuffer[50];
    const char	*pszHemisphere = NULL;
    double	dfRound;
    int		i;

    dfRound = 0.5/60;
    for( i = 0; i < nPrecision; i++ )
        dfRound = dfRound * 0.1;

    nDegrees = (int) ABS(dfAngle);
    nMinutes = (int) ((ABS(dfAngle) - nDegrees) * 60 + dfRound);
    dfSeconds = ABS((ABS(dfAngle) * 3600 - nDegrees*3600 - nMinutes*60));

    if( EQUAL(pszAxis,"Long") && dfAngle < 0.0 )
        pszHemisphere = "W";
    else if( EQUAL(pszAxis,"Long") )
        pszHemisphere = "E";
    else if( dfAngle < 0.0 )
        pszHemisphere = "S";
    else
        pszHemisphere = "N";

    sprintf( szFormat, "%%3dd%%2d\'%%%d.%df\"%s",
             nPrecision+3, nPrecision, pszHemisphere );
    sprintf( szBuffer, szFormat, nDegrees, nMinutes, dfSeconds );

    return( szBuffer );
}
