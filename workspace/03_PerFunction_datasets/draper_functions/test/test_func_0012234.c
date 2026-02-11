FuncPOSITION_SORTED_LIST (
    Obj                 self,
    Obj                 list,
    Obj                 obj )
{
    UInt                h;


    while ( ! IS_SMALL_LIST(list) ) {
        list = ErrorReturnObj(
            "POSITION_SORTED_LIST: <list> must be a small list (not a %s)",
            (Int)TNAM_OBJ(list), 0L,
            "you can replace <list> via 'return <list>;'" );
    }


    if ( IS_DENSE_PLIST(list) ) {
        h = PositionSortedDensePlist( list, obj );
    }
    else {
        h = POSITION_SORTED_LIST( list, obj );
    }


    return INTOBJ_INT( h );
}
