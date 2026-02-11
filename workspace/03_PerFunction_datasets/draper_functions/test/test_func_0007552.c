getablexprdepth( Expr )

  ablexpr *Expr;
{
  long  NumberOper;
  long  MaxDepth;
  long  CarDepth;

  if ( ABL_ATOM( Expr ) )
  {
    return( 0 );
  }

  MaxDepth   = 0;
  NumberOper = 0;

  while ( ( Expr = ABL_CDR( Expr ) ) != (chain_list *)0 )
  {
    CarDepth = getablexprdepth( ABL_CAR( Expr ) );

    if ( CarDepth > MaxDepth ) MaxDepth = CarDepth;

    NumberOper++;
  }

  if ( NumberOper > 1 ) NumberOper--;

  return( MaxDepth + NumberOper );
}
