EvalIsbComObjName (
    Expr                expr )
{
    Obj                 isb;
    Obj                 record;
    UInt                rnam;


    record = EVAL_EXPR( ADDR_EXPR(expr)[0] );


    rnam = (UInt)(ADDR_EXPR(expr)[1]);


    if ( TNUM_OBJ(record) == T_COMOBJ ) {
        isb = (IsbPRec( record, rnam ) ? True : False);
    }
    else {
        isb = (ISB_REC( record, rnam ) ? True : False);
    }


    return isb;
}
