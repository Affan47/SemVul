EvalRefGVar (
    Expr                expr )
{
    Obj                 val;


    if ( (val = VAL_GVAR( (UInt)(ADDR_EXPR(expr)[0]) )) == 0
      && (val = ValAutoGVar( (UInt)(ADDR_EXPR(expr)[0]) )) == 0 ) {
        while ( (val = VAL_GVAR( (UInt)(ADDR_EXPR(expr)[0]) )) == 0
             && (val = ValAutoGVar( (UInt)(ADDR_EXPR(expr)[0]) )) == 0 ) {
            ErrorReturnVoid(
                "Variable: '%s' must have an assigned value",
                (Int)NameGVar( (UInt)(ADDR_EXPR(expr)[0]) ), 0L,
                "you can 'return;' after assigning a value" );
        }
    }


    return val;
}
