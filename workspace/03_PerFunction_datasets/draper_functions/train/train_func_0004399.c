IntrIfEndBody (
    UInt                nr )
{
    UInt                i;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 1 ) { IntrIgnoring--; return; }
    if ( IntrCoding    > 0 ) { CodeIfEndBody( nr ); return; }


    if ( IntrIgnoring == 1 ) {
        IntrIgnoring = 0;
        return;
    }


    for ( i = nr; 1 <= i; i-- ) {
        PopVoidObj();
    }


    IntrIgnoring = 1;
}
