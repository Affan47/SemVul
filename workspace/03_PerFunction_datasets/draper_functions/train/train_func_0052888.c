EvalIsbList (
    Expr                expr )
{
    Obj                 list;
    Obj                 pos;
    Int                 p;


    list = EVAL_EXPR( ADDR_EXPR(expr)[0] );


    pos = EVAL_EXPR( ADDR_EXPR(expr)[1] );
    if (IS_INTOBJ(pos))
      {
        p = INT_INTOBJ( pos );
        return (ISB_LIST( list, p ) ? True : False);
      }
    else
      return ISBB_LIST(list, pos) ? True : False;
}
