VasySimulateVexCompare( Expr )

  vexexpr *Expr;
{
  vasysimul       *SimulExpr1;
  vasysimul       *SimulExpr2;
  char           *SimulValue1;
  chain_list     *ScanChain;
  vexexpr        *Operand;
  long            Oper;
  short           Compare;
  short           Negative;
  short           Zero;
  int             Position;

  Oper = GetVexOperValue( Expr );

  ScanChain = Expr->OPERAND;
  Operand   = GetVexOperand( ScanChain );
  SimulExpr1 = VasySimulateVex( Operand );

  ScanChain = ScanChain->NEXT;
  Operand   = GetVexOperand( ScanChain );
  SimulExpr2 = VasySimulateVex( Operand );

  SimulExpr2 = VasySimulateNegSimul( SimulExpr2 );
  SimulExpr1 = VasySimulateSumSimul( SimulExpr1, SimulExpr2 );

  SimulValue1 = SimulExpr1->VALUE;

  Negative = ( SimulValue1[ 0 ] == VEX_ONE_ID );
  Zero     = 1;

  for ( Position = SimulExpr1->WIDTH - 1; Position >= 0; Position-- )
  {
    if ( SimulValue1[ Position ] != VEX_ZERO_ID )
    {
      Zero = 0; break;
    }
  }

  if ( Oper == VEX_LT ) Compare = (   Negative ) && ( ! Zero );
  else
  if ( Oper == VEX_GT ) Compare = ( ! Negative ) && ( ! Zero );
  else
  if ( Oper == VEX_LE ) Compare = (   Negative ) || (   Zero );
  else
                        Compare = ( ! Negative ) || (   Zero );

  VasySimulateDelSimul( SimulExpr1 );

  SimulExpr1 = VasySimulateAddSimul( 1, 0 );

  if ( Compare ) SimulExpr1->VALUE[ 0 ] = VEX_ONE_ID;
  else           SimulExpr1->VALUE[ 0 ] = VEX_ZERO_ID;

  return( SimulExpr1 );
}
