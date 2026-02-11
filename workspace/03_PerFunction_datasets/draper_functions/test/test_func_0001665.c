VasyRedInstWhile( BeginPlace )

  vpnplace_list *BeginPlace;
{
  vpnplace_list *TestPlace;
  vpnplace_list *EndPlace;
  vpnplace_list *CasePlace;
  vpntrans_list *CaseTrans;
  vpntrans_list *TestTrans;
  vpnarc        *VpnArc;
  chain_list    *ScanChain;

  if ( IsVasyDebugLevel2() )
  {
    VasyPrintf( stdout, "  --> VasyRedInstWhile %s\n", BeginPlace->NAME );
  }

  EndPlace = BeginPlace->LINK;
  BeginPlace->LINK = (vpnplace_list *)0;

  SetVasyRedInstTag( BeginPlace );
  SetVasyRedInstTag( EndPlace   );

  VpnArc    = GetVpnArc( BeginPlace->TRANS_OUT );
  TestTrans = GetVpnArcTargetTrans( VpnArc );
  VpnArc    = GetVpnArc( TestTrans->PLACE_OUT );
  TestPlace = GetVpnArcTargetPlace( VpnArc );

  for ( ScanChain  = TestPlace->TRANS_OUT;
        ScanChain != (chain_list *)0;
        ScanChain  = ScanChain->NEXT )
  {
    VpnArc    = GetVpnArc( ScanChain );
    CaseTrans = GetVpnArcTargetTrans( VpnArc );
    VpnArc    = GetVpnArc( CaseTrans->PLACE_OUT );
    CasePlace = GetVpnArcTargetPlace( VpnArc );

    VasyPrevTrans = CaseTrans;

    VasyRedInstVpnPlace( CasePlace );

    VasyPrevTrans = VasyRedInstVertical( TestPlace, VasyPrevTrans );
  }

  ClearVasyRedInstTag( EndPlace   );

  VpnArc       = GetVpnArc( EndPlace->TRANS_OUT );
  VasyPrevTrans = GetVpnArcTargetTrans( VpnArc );

  if ( IsVasyDebugLevel2() )
  {
    VasyPrintf( stdout, "  <-- VasyRedInstWhile %s\n", EndPlace->NAME );
  }
}
