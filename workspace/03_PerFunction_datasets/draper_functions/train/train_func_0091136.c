FuncCALL_FUNC (
    Obj                 self,
    Obj                 args )
{
    Obj                 result;
    Obj                 func;
    Obj                 list2;
    Obj                 arg;
    UInt                i;


    if ( LEN_LIST( args ) == 0 ) {
        func = ErrorReturnObj(
            "usage: CallFunction( <func>, <arg1>... )",
            0L, 0L,
            "you can replace function <func> via 'return <func>;'" );
    }
    else {
        func = ELMV_LIST( args, 1 );
    }


    while ( TNUM_OBJ( func ) != T_FUNCTION ) {
        func = ErrorReturnObj(
            "CallFunction: <func> must be a function",
            0L, 0L,
            "you can replace function <func> via 'return <func>;'" );
    }


    if      ( LEN_LIST(args) == 1 ) {
        result = CALL_0ARGS( func );
    }
    else if ( LEN_LIST(args) == 2 ) {
        result = CALL_1ARGS( func, ELMV_LIST(args,2) );
    }
    else if ( LEN_LIST(args) == 3 ) {
        result = CALL_2ARGS( func, ELMV_LIST(args,2), ELMV_LIST(args,3) );
    }
    else if ( LEN_LIST(args) == 4 ) {
        result = CALL_3ARGS( func, ELMV_LIST(args,2), ELMV_LIST(args,3),
                                   ELMV_LIST(args,4) );
    }
    else if ( LEN_LIST(args) == 5 ) {
        result = CALL_4ARGS( func, ELMV_LIST(args,2), ELMV_LIST(args,3),
                                   ELMV_LIST(args,4), ELMV_LIST(args,5) );
    }
    else if ( LEN_LIST(args) == 6 ) {
        result = CALL_5ARGS( func, ELMV_LIST(args,2), ELMV_LIST(args,3),
                                   ELMV_LIST(args,4), ELMV_LIST(args,5),
                                   ELMV_LIST(args,6) );
    }
    else if ( LEN_LIST(args) == 7 ) {
        result = CALL_6ARGS( func, ELMV_LIST(args,2), ELMV_LIST(args,3),
                                   ELMV_LIST(args,4), ELMV_LIST(args,5),
                                   ELMV_LIST(args,6), ELMV_LIST(args,7) );
    }
    else {
        list2 = NEW_PLIST( T_PLIST, LEN_LIST(args)-1 );
        SET_LEN_PLIST( list2, LEN_LIST(args)-1 );
        for ( i = 1; i <= LEN_LIST(args)-1; i++ ) {
            arg = ELMV_LIST( args, (Int)(i+1) );
            SET_ELM_PLIST( list2, i, arg );
        }
        result = CALL_XARGS( func, list2 );
    }


    return result;
}
