ExecAssComObjName (
    Stat                stat )
{
    Obj                 record;
    UInt                rnam;
    Obj                 rhs;


    SET_BRK_CURR_STAT( stat );
    record = EVAL_EXPR( ADDR_STAT(stat)[0] );


    rnam = (UInt)(ADDR_STAT(stat)[1]);


    rhs = EVAL_EXPR( ADDR_STAT(stat)[2] );


    if ( TNUM_OBJ(record) == T_COMOBJ ) {
        AssPRec( record, rnam, rhs );
    }
    else {
        ASS_REC( record, rnam, rhs );
    }


    return 0;
}
