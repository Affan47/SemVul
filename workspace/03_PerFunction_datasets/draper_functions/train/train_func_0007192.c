VasyDisplayLines( VpnLine )

  vpnline_list *VpnLine;
{
  if ( VpnLine != (vpnline_list *)0 )
  {
    fprintf( stderr, " in line [" );

    while ( VpnLine != (vpnline_list *)0 )
    {
      fprintf( stderr, "%ld", VpnLine->LINE );

      if ( VpnLine->NEXT != (vpnline_list *)0 )
      {
        fprintf( stderr, "," );
      }

      VpnLine = VpnLine->NEXT;
    }

    fprintf( stderr, "]" );
  }
}
