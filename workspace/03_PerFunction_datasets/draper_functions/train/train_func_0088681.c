VasySupportUsedVpnSymbol( AsgSymbol )

  vpnsym *AsgSymbol;
{
  vpnact_list    *VpnAction;
  vpndecl_list   *AsgDeclar;
  vpnsym         *VpnSymbol;
  vexexpr        *AsgAtom;
  authelem       *Element;
  vasyactinfo     *ActInfo;
  chain_list    **Support;
  unsigned char  *Flags;
  chain_list     *ScanChain;
  int             AsgPos;

  AsgDeclar = AsgSymbol->DECL;

  if ( ! isvextypedivisible( AsgDeclar->BASE ) )
  {
    Element = searchauthelem( VasyHashAssign, AsgSymbol->NAME );
  }
  else
  {
    Element = searchauthelem( VasyHashBitVec, (char*)AsgSymbol );
  }

  if ( Element == (authelem *)0 ) return;

  VpnAction = (vpnact_list *)Element->VALUE;
  ActInfo   = GetVasyVpnActInfo( VpnAction );

  Support   = ActInfo->SUPPORT;
  Flags     = ActInfo->FLAGS;

  AsgAtom = VpnAction->VEX_ATOM;
  AsgPos  = getvexvectorpos( AsgAtom, AsgSymbol->INDEX );

  if ( ! IsVasyVpnActInfoUsed( Flags[ AsgPos ] ) )
  {
    SetVasyVpnActInfoUsed( Flags[ AsgPos ] );

    for ( ScanChain  = Support[ AsgPos ];
          ScanChain != (chain_list *)0;
          ScanChain  = ScanChain->NEXT )
    {
      VpnSymbol = (vpnsym *)ScanChain->DATA;

      if ( VpnSymbol != AsgSymbol )
      {
        VasySupportUsedVpnSymbol( VpnSymbol );
      }
    }
  }
}
