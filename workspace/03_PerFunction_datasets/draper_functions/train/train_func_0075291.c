VasyRedInstLocalVpnProc( VpnFigure, VpnProc )

   vpnfig_list  *VpnFigure;
   vpnproc_list *VpnProc;
{
  vpnplace_list *ScanPlace;
  vpnplace_list *NextPlace;
  vpnplace_list *PrevPlace;
  vpnplace_list *EndPlace;
  vpntrans_list *ScanTrans;
  vpntrans_list *PrevTrans;
  vpntrans_list *NewTrans;
  vpnarc        *VpnArc;
  chain_list    *ScanChain;
  int            Modified;

  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "--> VasyRedInstLocalVpnProc %s\n", VpnProc->NAME );
    VasyDebugSaveVpnFig( VasyFigure );
  }

  VasyFigure    = VpnFigure;
  VasyProcess   = VpnProc;

  Modified = 1;

  while ( Modified )
  {
    Modified = 0;

    ScanPlace = VpnProc->PLACE;

    while ( ScanPlace != (vpnplace_list *)0 )
    {
      NextPlace = ScanPlace->NEXT;

      if ( ScanPlace->NUMBER_OUT > 1 )
      {
        VpnArc    = GetVpnArc( ScanPlace->TRANS_OUT );
        ScanTrans = GetVpnArcTargetTrans( VpnArc );
        VpnArc    = GetVpnArc( ScanTrans->PLACE_OUT );
        EndPlace  = GetVpnArcTargetPlace( VpnArc );

        if ( VasyRedInstLateral( ScanPlace, EndPlace, 0 ) )
        {
          Modified = 1;
        }
      }

      if ( ( ScanPlace->NUMBER_IN  == 1 ) &&
           ( ScanPlace->NUMBER_OUT == 1 ) )
      {
        VpnArc    = GetVpnArc( ScanPlace->TRANS_OUT );
        ScanTrans = GetVpnArcTargetTrans( VpnArc );
        VpnArc    = GetVpnArc( ScanPlace->TRANS_IN );
        PrevTrans = GetVpnArcSourceTrans( VpnArc );

        VpnArc    = GetVpnArc( PrevTrans->PLACE_IN );
        PrevPlace = GetVpnArcSourcePlace( VpnArc );
        NewTrans  = VasyRedInstVertical( PrevPlace, ScanTrans );

        if ( NewTrans != ScanTrans )
        {
          Modified = 1;
        }
      }
      else
      if ( ScanPlace->NUMBER_IN == 0 )
      {
        ScanChain = ScanPlace->TRANS_OUT;

        while ( ScanChain != (chain_list *)0 )
        {
          VpnArc    = GetVpnArc( ScanChain );
          ScanChain = ScanChain->NEXT;
          ScanTrans = GetVpnArcTargetTrans( VpnArc );

          delvpntrans( VpnFigure, ScanTrans );
        }

        delvpnplace( VpnFigure, ScanPlace );

        Modified = 1;
      }

      ScanPlace = NextPlace;
    }

    if ( Modified && IsVasyDebugLevel1() )
    {
      VasyDebugSaveVpnFig( VasyFigure );
    }
  }

  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "<-- VasyRedInstLocalVpnProc %s\n", VpnProc->NAME );
  }
}
