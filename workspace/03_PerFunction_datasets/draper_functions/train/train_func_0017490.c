FuncUNB_GF2MAT (
    Obj                 self,
    Obj                 list,
    Obj                 pos )
{
    UInt                p;


    if ( ! IS_MUTABLE_OBJ(list) ) {
        ErrorReturnVoid(
            "Lists Assignment: <list> must be a mutable list",
            0L, 0L,
            "you can 'return;' and ignore the assignment" );
        return 0;
    }


    if (!IS_INTOBJ(pos))
      ErrorMayQuit("UNB_GF2MAT: position must be a small integer, not a %s",
		(Int)TNAM_OBJ(pos),0L);
    p = INT_INTOBJ(pos);


    if ( p > 1 && LEN_GF2MAT(list) < p ) {
        ;
    }
    else if ( LEN_GF2MAT(list) == p ) {
        ResizeBag( list, SIZE_PLEN_GF2MAT(p-1) );
        SET_LEN_GF2MAT( list, p-1 );
    }
    else {
        PlainGF2Mat(list);
        UNB_LIST( list, p );
    }
    return 0;
}
