PrintExpr (
    Expr                expr )
{
    (*PrintExprFuncs[ TNUM_EXPR(expr) ])( expr );
}
