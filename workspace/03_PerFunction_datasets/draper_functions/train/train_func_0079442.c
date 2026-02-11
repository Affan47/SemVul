SetNode( const char *pszNodePath,
                                     double dfValue )

{
    char        szValue[64];

    if( ABS(dfValue - (int) dfValue) == 0.0 )
        sprintf( szValue, "%d", (int) dfValue );
    else
        OGRPrintDouble( szValue, dfValue );

    return SetNode( pszNodePath, szValue );
}
