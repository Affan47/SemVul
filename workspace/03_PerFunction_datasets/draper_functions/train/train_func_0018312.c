GetStringField( const char * pszFieldPath, CPLErr *peErr,
                                      int *pnRemainingDataSize)

{
    char *pszResult = NULL;

    if( !GetFieldValue( pszFieldPath, 's', &pszResult, pnRemainingDataSize ) )
    {
        if( peErr != NULL )
            *peErr = CE_Failure;

        return NULL;
    }
    else
    {
        if( peErr != NULL )
            *peErr = CE_None;

        return pszResult;
    }
}
