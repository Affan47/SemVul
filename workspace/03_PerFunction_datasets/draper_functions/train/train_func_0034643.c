AddMOLfileError( char *pStrErr, const char *szMsg )
{
    if ( pStrErr && szMsg && szMsg[0] ) {
        int lenStrErr = strlen( pStrErr );
        int lenMsg    = strlen( szMsg );
        char *p = strstr( pStrErr, szMsg );
        if ( p && (p==pStrErr || *(p-1) == ' ' && (*(p-2) == ';' || *(p-2) == ':' )) &&
                  (p+lenMsg == pStrErr+lenStrErr ||
                  p[lenMsg] == ';' && p[lenMsg+1] == ' ' ||
                  p[lenMsg-1]==':' && p[lenMsg]==' ') ) {
            return 1;
        }
        if ( lenStrErr + lenMsg + 2*(lenStrErr > 0) < STR_ERR_LEN ) {

            if (lenStrErr > 0) {
                if ( pStrErr[lenStrErr-1] != ':' ) {
                    strcat( pStrErr, ";" );
                }
                strcat( pStrErr, " " );
            }
            strcat( pStrErr, szMsg );
            return 1;
        }

        if ( strstr( pStrErr, "..." ) ) {
            return 0;
        }
        if ( lenStrErr + 3 < STR_ERR_LEN ) {
            strcat( pStrErr, "..." );
        }
    }
    return 0;
}
