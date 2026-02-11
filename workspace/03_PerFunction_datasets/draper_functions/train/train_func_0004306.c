VasySupportEventBitVex( Expr )

  vexexpr *Expr;
{
  vpndecl_list   *VpnDeclar;
  vpnsym         *VpnSymbol;
  char           *AtomName;
  chain_list     *ScanChain;
  vexexpr        *Operand;
  long            Oper;
  int             Index;

  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "VasySupportEventBitVex -> \n" );
    viewvexexprboundln( Expr );
  }

  if ( IsVexNodeOper( Expr ) )
  {
    Oper = GetVexOperValue( Expr );

    if ( Oper == VEX_EVENT )
    {
      Expr = GetVexOperand( Expr->OPERAND );

      AtomName  = GetVexAtomValue( Expr );
      VpnDeclar = searchvpndeclall( VasyFigure, AtomName );

      Index     = getvexvectorindex( Expr, 0 );
      VpnSymbol = getvpnsymdecl( VpnDeclar, Index );

      VasySupportEventBitVpnSymbol( VpnSymbol );
    }
    else
    {
      for ( ScanChain  = Expr->OPERAND;
            ScanChain != (chain_list *)0;
            ScanChain  = ScanChain->NEXT )
      {
        Operand = GetVexOperand( ScanChain );
        VasySupportEventBitVex( Operand );
      }
    }
  }
}
