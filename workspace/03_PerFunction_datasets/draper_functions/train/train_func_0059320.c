VasySimulateGetVpnActAtom( VpnFigure, VpnAction )

  vpnfig_list *VpnFigure;
  vpnact_list *VpnAction;
{
  vasysimul   *SimulExpr1;
  chain_list *ScanChain;
  vexexpr    *VexExpr;
  vexexpr    *VexAtom;
  vexexpr    *Operand;
  long        Oper;
  int         IndexFrom;
  int         IndexTo;
  int         IndexMin;
  int         IndexMax;
  int         Width;
  int         PosMin;
  int         PosMax;

  VexExpr = VpnAction->VEX_ATOM;

  if ( IsVexNodeAtom( VexExpr ) ) return( VexExpr );

  if ( ! IsVexNodeOper( VexExpr ) )
  {
    VasyErrorLine( VASY_ERROR_IN_SIMULATION, VpnAction->LINE, "bad assigment" );
  }

  Oper = GetVexOperValue( VexExpr );

  if ( ( Oper != VEX_INDEX  ) &&
       ( Oper != VEX_DOWNTO ) &&
       ( Oper != VEX_TO     ) )
  {
    VasyErrorLine( VASY_ERROR_IN_SIMULATION, VpnAction->LINE, "bad assigment" );
  }

  VasyFigure  = VpnFigure;
  VasyVpnLine = VpnAction->LINE;

  ScanChain  = VexExpr->OPERAND;
  VexAtom    = GetVexOperand( ScanChain );

  ScanChain  = ScanChain->NEXT;
  Operand    = GetVexOperand( ScanChain );
  SimulExpr1 = VasySimulateVex( Operand );

  IndexFrom  = VasySimulateIntegerSimul( SimulExpr1 );
  VasySimulateDelSimul( SimulExpr1 );

  if ( Oper != VEX_INDEX )
  {
    ScanChain  = ScanChain->NEXT;
    Operand    = GetVexOperand( ScanChain );
    SimulExpr1 = VasySimulateVex( Operand );

    IndexTo = VasySimulateIntegerSimul( SimulExpr1 );
    VasySimulateDelSimul( SimulExpr1 );
  }
  else
  {
    IndexTo = IndexFrom;
  }

  VexExpr = dupvexnode( VexAtom );

  if ( Oper == VEX_DOWNTO )
  {
    IndexMin = IndexTo;
    IndexMax = IndexFrom;

    SetVexAtomDown( VexExpr );
  }
  else
  {
    IndexMin = IndexFrom;
    IndexMax = IndexTo;

    SetVexAtomUp( VexExpr );
  }

  Width = ( IndexMax - IndexMin ) + 1;

  if ( Width <= 0 )
  {
    VasyErrorLine( VASY_ERROR_IN_SIMULATION, VpnAction->LINE, "negative width" );
  }

  PosMin = getvexvectorpos( VexAtom, IndexMin );
  PosMax = getvexvectorpos( VexAtom, IndexMax );

  if ( ( PosMin == -1 ) ||
       ( PosMax == -1 ) )
  {
    VasyErrorLine( VASY_ERROR_IN_SIMULATION, VpnAction->LINE, "index out of bound" );
  }

  VexExpr->LEFT  = IndexFrom;
  VexExpr->RIGHT = IndexTo;
  VexExpr->WIDTH = Width;

  SetVexAtomStaWidth( VexExpr );

  return( VexExpr );
}
