CSVScanLines( FILE *fp, int iKeyField, const char * pszValue,
                     CSVCompareCriteria eCriteria )

{
    char        **papszFields = NULL;
    int         bSelected = FALSE, nTestValue;

    CPLAssert( pszValue != NULL );
    CPLAssert( iKeyField >= 0 );
    CPLAssert( fp != NULL );

    nTestValue = atoi(pszValue);

    while( !bSelected ) {
        papszFields = CSVReadParseLine( fp );
        if( papszFields == NULL )
            return( NULL );

        if( CSLCount( papszFields ) < iKeyField+1 )
        {

        }
        else if( eCriteria == CC_Integer
                 && atoi(papszFields[iKeyField]) == nTestValue )
        {
            bSelected = TRUE;
        }
        else
        {
            bSelected = CSVCompare( papszFields[iKeyField], pszValue,
                                    eCriteria );
        }

        if( !bSelected )
        {
            CSLDestroy( papszFields );
            papszFields = NULL;
        }
    }

    return( papszFields );
}
