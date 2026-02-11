PrintRangeExpr (
    Expr                expr )
{
    if ( SIZE_EXPR( expr ) == 2*sizeof(Expr) ) {
        Pr("%2>[ %2>",0L,0L);    PrintExpr( ADDR_EXPR(expr)[0] );
        Pr("%2< .. %2>",0L,0L);  PrintExpr( ADDR_EXPR(expr)[1] );
        Pr(" %4<]",0L,0L);
    }
    else {
        Pr("%2>[ %2>",0L,0L);    PrintExpr( ADDR_EXPR(expr)[0] );
        Pr("%<,%< %2>",0L,0L);   PrintExpr( ADDR_EXPR(expr)[1] );
        Pr("%2< .. %2>",0L,0L);  PrintExpr( ADDR_EXPR(expr)[2] );
        Pr(" %4<]",0L,0L);
    }
}
