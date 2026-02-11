inchi_fgetsLfTab( char *szLine, int len, FILE *f )
{
    int  length;
    char *p;
    char szSkip[256];
    int  bTooLongLine = 0;
    do {
        p = inchi_fgetsTab( szLine, len, f );
        if ( !p ) {
            return -1;
        }
        bTooLongLine = ( (int)strlen(szLine) == len-1 && szLine[len-2] != '\n' );
        LtrimRtrim( szLine, &length );
    } while ( !length );
    if ( bTooLongLine ) {
        while ( p = inchi_fgetsTab( szSkip, sizeof(szSkip)-1, f ) ) {
            if ( strchr( szSkip, '\n' ) )
                break;
        }
    }
    return length;
}
