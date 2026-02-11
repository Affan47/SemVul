GetInChIFormulaNumH( INChI *pInChI, int *nNumH )
{
    const char *p, *q;
    *nNumH = 0;
    if ( pInChI->szHillFormula ) {
        for ( p = strchr( pInChI->szHillFormula, 'H'); p; p = strchr(p, 'H') ) {
            p ++;
            if ( !islower( UCINT *p ) ) {

                if ( isdigit( UCINT *p ) ) {
                    *nNumH += (int)inchi_strtol( p, &q, 10 );
                    p = q;
                } else {
                    *nNumH += 1;
                }
            }
        }
    }
    return 0;
}
