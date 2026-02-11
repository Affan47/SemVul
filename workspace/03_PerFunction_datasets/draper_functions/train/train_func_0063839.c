freevexexpr( Expr )

  vexexpr *Expr;
{
  chain_list *ScanOper;

  if ( Expr != (vexexpr *)0 )
  {
    if ( ! IsVexNodeAtom( Expr ) )
    {
      for ( ScanOper  = Expr->OPERAND;
            ScanOper != (chain_list *)0;
            ScanOper  = ScanOper->NEXT )
      {
        freevexexpr( GetVexOperand( ScanOper ) );
      }

      freechain( Expr->OPERAND );
    }

    freevexnode( Expr );
  }
}
