createablxorbinexpr( Oper, Expr1, Expr2 )

  long        Oper;
  ablexpr *Expr1;
  ablexpr *Expr2;
{
  ablexpr *Expr;
  ablexpr *NotExpr1;
  ablexpr *NotExpr2;

  if ( ( Oper != ABL_XOR  ) &&
       ( Oper != ABL_NXOR ) )
  {
    ablerror( ABL_OPERATOR_ERROR, Oper );
  }

  NotExpr1 = createablnotexpr( dupablexpr( Expr1 ) );
  NotExpr2 = createablnotexpr( dupablexpr( Expr2 ) );

  if ( Oper == ABL_XOR )
  {
    Expr = createablbinexpr( ABL_OR,
                             createablbinexpr( ABL_AND, NotExpr1, Expr2    ),
                             createablbinexpr( ABL_AND, Expr1   , NotExpr2 ) );
  }
  else
  {
    Expr = createablbinexpr( ABL_OR,
                             createablbinexpr( ABL_AND, NotExpr1, NotExpr2 ),
                             createablbinexpr( ABL_AND, Expr1   , Expr2    ) );
  }

  return( Expr );
}
