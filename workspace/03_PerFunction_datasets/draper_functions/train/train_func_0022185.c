SelectClass( const char *pszAcronym )

{
    for( int i = 0; i < nClasses; i++ )
    {
        if( !SelectClassByIndex( i ) )
            continue;

        if( strcmp(GetAcronym(),pszAcronym) == 0 )
            return TRUE;
    }

    return FALSE;
}
