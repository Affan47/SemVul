VpnWriteModel( VpnFigure )

  vpnfig_list *VpnFigure;
{
  vpnmod_list  *ScanMod;
  vpnport_list *ScanPort;
  vpngen_list  *ScanGen;

  for ( ScanMod  = VpnFigure->MODEL;
        ScanMod != (vpnmod_list *)0;
        ScanMod  = ScanMod->NEXT )
  {
    fprintf( VpnFile, "MODEL\t%ld\t%s\n",
             (long)ScanMod->FLAGS,
             ScanMod->NAME );

    VpnWriteLine( ScanMod->LINE );

    for ( ScanPort  = ScanMod->PORT;
          ScanPort != (vpnport_list *)0;
          ScanPort  = ScanPort->NEXT )
    {
      fprintf( VpnFile, "PORT\t%ld\t%ld\t%ld",
               (long)ScanPort->DIR,
               (long)ScanPort->BASE,
               (long)ScanPort->FLAGS );

      VpnWriteExpr( "", ScanPort->VEX_ATOM );
      VpnWriteLine( ScanPort->LINE );
    }

    for ( ScanGen  = ScanMod->GENERIC;
          ScanGen != (vpngen_list *)0;
          ScanGen  = ScanGen->NEXT )
    {
      fprintf( VpnFile, "GEN_MOD\t%ld\t%ld\t",
               (long)ScanGen->BASE,
               (long)ScanGen->FLAGS );

      VpnWriteExpr( "", ScanGen->VEX_ATOM );

      VpnWriteExpr( "GEN_EXPR", ScanGen->VEX_EXPR );

      VpnWriteLine( ScanGen->LINE );
    }
  }
}
