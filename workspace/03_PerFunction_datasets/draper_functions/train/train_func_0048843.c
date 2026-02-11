simpvpntrans( VpnTrans )

  vpntrans_list *VpnTrans;
{
  vpnact_list *VpnAct;

  VpnTrans->VEX_GUARD = simpvexexpr( VpnTrans->VEX_GUARD );

  for ( VpnAct  = VpnTrans->ACT;
        VpnAct != (vpnact_list *)0;
        VpnAct  = VpnAct->NEXT )
  {
    simpvpnact( VpnAct );
  }
}
