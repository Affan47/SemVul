FuncLIST_BLIST (
    Obj                 self,
    Obj                 list,
    Obj                 blist )
{
    Obj                 sub;
    Int                 len;
    UInt                n;
    UInt                nn;
    UInt                i;


    while ( ! IS_SMALL_LIST( list ) ) {
        list = ErrorReturnObj(
            "ListBlist: <list> must be a small list (not a %s)",
            (Int)TNAM_OBJ(list), 0L,
            "you can replace <list> via 'return <list>;'" );
    }

    while ( ! IsBlistConv( blist ) ) {
        blist = ErrorReturnObj(
            "ListBlist: <blist> must be a boolean list (not a %s)",
            (Int)TNAM_OBJ(blist), 0L,
            "you can replace <blist> via 'return <blist>;'" );
    }
    while ( LEN_LIST( list ) != LEN_BLIST( blist ) ) {
        blist = ErrorReturnObj(
            "ListBlist: <blist> must have the same length as <list> (%d)",
            LEN_PLIST( list ), 0L,
            "you can replace <blist> via 'return <blist>;'" );
    }


    n = SizeBlist(blist);


    sub = NEW_PLIST( IS_MUTABLE_OBJ(list) ? T_PLIST : T_PLIST+IMMUTABLE, n );
    SET_LEN_PLIST( sub, n );


    len = LEN_LIST( list );
    nn  = 1;
    for ( i = 1;  nn <= n && i <= len;  i++  ) {
        if ( ELM_BLIST( blist, i ) == True ) {
            SET_ELM_PLIST( sub, (Int)nn, ELMW_LIST( list, (Int)i ) );
            CHANGED_BAG( sub );
            nn++;
        }
    }


    return sub;
}
