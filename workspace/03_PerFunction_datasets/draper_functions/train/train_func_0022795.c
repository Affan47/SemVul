FuncCONV_BLIST (
    Obj                 self,
    Obj                 blist )
{

    while ( ! IsBlistConv(blist) ) {
        blist = ErrorReturnObj(
            "CONV_BLIST: <blist> must be a boolean list (not a %s)",
            (Int)TNAM_OBJ(blist), 0L,
            "you can replace <blist> via 'return <blist>;'" );
    }


    return 0;
}
