EvalElmRecExpr (
    Expr                expr )
{
    Obj                 elm;
    Obj                 record;
    UInt                rnam;


    record = EVAL_EXPR( ADDR_EXPR(expr)[0] );


    rnam = RNamObj( EVAL_EXPR( ADDR_EXPR(expr)[1] ) );


    elm = ELM_REC( record, rnam );


    return elm;
}
