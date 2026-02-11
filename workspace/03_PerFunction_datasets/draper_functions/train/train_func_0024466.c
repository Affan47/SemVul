loc_getvexallname( Expr )

  vexexpr *Expr;
{
  chain_list *ScanOper;

  if ( IsVexNodeAtom( Expr ) )
  {
    loc_getvexallnameatom( Expr );
  }
  else
  {
    for ( ScanOper  = Expr->OPERAND;
          ScanOper != (chain_list *)0;
          ScanOper  = ScanOper->NEXT )
    {
      loc_getvexallname( GetVexOperand( ScanOper ) );
    }
  }
}
