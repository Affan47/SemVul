loc_viewvbcas( ScanCase  )

  vbcas_list  *ScanCase;
{
  vbcho_list    *ScanChoice;
  chain_list    *ScanChain;
  int            Offset;

  fprintf( stdout, "[%ld] ", ScanCase->LINE );
  fprintf( stdout, "CASE (" );
  viewvexexprbound( ScanCase->VEX );
  fprintf( stdout, ") IS\n" );

  for ( Offset = 0; Offset < ScanCase->SIZE; Offset++ )
  {
    ScanChoice = &ScanCase->CHOICE[ Offset ];

    fprintf( stdout, "WHEN " );

    for ( ScanChain  = ScanChoice->VALUES;
          ScanChain != (chain_list *)0;
          ScanChain  = ScanChain->NEXT )
    {
      fprintf( stdout, "%s ", (char *)ScanChain->DATA );

      if ( ScanChain->NEXT != (chain_list *)0 )
      {
        fprintf( stdout, " | " );
      }
    }

    fprintf( stdout, "=> " );

    vbh_viewvbinst( ScanChoice->INSTRUCTION );
  }

  fprintf( stdout, "END CASE\n" );
}
