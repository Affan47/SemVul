completion_gvar (
    Char *              name,
    UInt                len )
{
    Char *              curr;
    Char *              next;
    UInt                i, k;

    next = 0;
    for ( i = 1; i <= CountGVars; i++ ) {

        if ( VAL_GVAR( i ) || ELM_PLIST( ExprGVars, i )) {
            curr = NameGVar( i );
            for ( k = 0; name[k] != 0 && curr[k] == name[k]; k++ ) ;
            if ( k < len || curr[k] <= name[k] )  continue;
            if ( next != 0 ) {
                for ( k = 0; curr[k] != '\0' && curr[k] == next[k]; k++ ) ;
                if ( k < len || next[k] < curr[k] )  continue;
            }
            next = curr;
        }
    }

    if ( next != 0 ) {
        for ( k = 0; next[k] != '\0'; k++ )
            name[k] = next[k];
        name[k] = '\0';
    }

    return next != 0;
}
