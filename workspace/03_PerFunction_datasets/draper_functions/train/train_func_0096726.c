EqSet (
    Obj                 listL,
    Obj                 listR )
{
    Int                 lenL;
    Int                 lenR;
    Obj                 elmL;
    Obj                 elmR;
    UInt                i;


    lenL = LEN_PLIST( listL );
    lenR = LEN_PLIST( listR );
    if ( lenL != lenR ) {
        return 0L;
    }


    for ( i = 1; i <= lenL; i++ ) {
        elmL = ELM_PLIST( listL, i );
        elmR = ELM_PLIST( listR, i );
        if ( ! EQ( elmL, elmR ) ) {
            return 0L;
        }
    }


    return 1L;
}
