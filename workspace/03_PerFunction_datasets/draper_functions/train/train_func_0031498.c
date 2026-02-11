RemoveCopyFopyInfo( void )
{
    UInt        i, l;

    l = LEN_PLIST(CopiesGVars);
    for ( i = 1; i <= l; i++ )
        SET_ELM_PLIST( CopiesGVars, i, 0 );
    l = LEN_PLIST(FopiesGVars);
    for ( i = 1; i <= l; i++ )
        SET_ELM_PLIST( FopiesGVars, i, 0 );
    NCopyAndFopyDone = 0;
    return;
}
