VasySimulateVexSlice( Expr )

  vexexpr *Expr;
{
  vasysimul   *SimulExpr1;
  vasysimul   *SimulExpr2;
  char       *SimulValue1;
  char       *SimulValue2;
  chain_list *ScanChain;
  vexexpr    *VexAtom;
  vexexpr    *Operand;
  long        Oper;
  int         IndexFrom;
  int         IndexTo;
  int         IndexMin;
  int         IndexMax;
  int         Index;
  int         Width;
  int         Position;
  int         ScanPos;
  short       Signed;

  Oper = GetVexOperValue( Expr );

  ScanChain   = Expr->OPERAND;
  VexAtom     = GetVexOperand( ScanChain );
  SimulExpr1  = VasySimulateVex( VexAtom );
  SimulValue1 = SimulExpr1->VALUE;

  ScanChain  = ScanChain->NEXT;
  Operand    = GetVexOperand( ScanChain );
  SimulExpr2 = VasySimulateVex( Operand );

  IndexFrom = VasySimulateIntegerSimul( SimulExpr2 );
  VasySimulateDelSimul( SimulExpr2 );

  if ( Oper != VEX_INDEX )
  {
    ScanChain  = ScanChain->NEXT;
    Operand    = GetVexOperand( ScanChain );
    SimulExpr2 = VasySimulateVex( Operand );

    IndexTo = VasySimulateIntegerSimul( SimulExpr2 );
    VasySimulateDelSimul( SimulExpr2 );
  }
  else
  {
    IndexTo = IndexFrom;
  }

  if ( IsVexAtomSigned( VexAtom ) ) Signed = 1;
  else                              Signed = 0;

  if ( Oper == VEX_DOWNTO )
  {
    IndexMin = IndexTo;
    IndexMax = IndexFrom;
  }
  else
  {
    IndexMin = IndexFrom;
    IndexMax = IndexTo;
  }

  Width = ( IndexMax - IndexMin ) + 1;

  if ( Width <= 0 )
  {
    VasyErrorLine( VASY_ERROR_IN_SIMULATION, VasyVpnLine, "negative width" );
  }

  SimulExpr2  = VasySimulateAddSimul( Width, Signed );
  SimulValue2 = SimulExpr2->VALUE;

  Position = 0;

  for ( Index = IndexMin; Index <= IndexMax; Index++ )
  {
    ScanPos = getvexvectorpos( VexAtom, Index );

    if ( ScanPos == -1 )
    {
      VasyErrorLine( VASY_ERROR_IN_SIMULATION, VasyVpnLine, "index out of bound" );
    }

    SimulValue2[ Position ] = SimulValue1[ ScanPos ];
  }

  VasySimulateDelSimul( SimulExpr1 );

  return( SimulExpr2 );
}
