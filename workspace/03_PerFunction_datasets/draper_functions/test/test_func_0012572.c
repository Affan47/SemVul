EvalRefLVar06 (
    Expr                expr )
{
    Obj                 val;


    if ( (val = OBJ_LVAR( 6 )) == 0 ) {
        while ( (val = OBJ_LVAR( 6 )) == 0 ) {
            ErrorReturnVoid(
                "Variable: '%s' must have an assigned value",
                (Int)NAME_LVAR( 6 ), 0L,
                "you can 'return;' after assigning a value" );
        }
    }


    return val;
}
