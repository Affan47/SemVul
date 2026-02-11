mapabloperexpr( Function, Oper, Expr )

  ablexpr *(*Function)();
  long        Oper;
  ablexpr *Expr;
{
  ablexpr *MapExpr;

  MapExpr = createabloper( Oper );

  while ( ( Expr = ABL_CDR( Expr ) ) != (ablexpr *)0 )
  {
    addablhexpr( MapExpr, (*Function)( ABL_CAR( Expr ) ) );
  }

  return( MapExpr );
}
