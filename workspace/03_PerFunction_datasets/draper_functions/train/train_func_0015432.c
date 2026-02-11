VasySupportBitVpnSymbol( VpnSymbol )

  vpnsym *VpnSymbol;
{
  authelem *Element;

  Element = searchauthelem( VasyHashSupportBit, (char*)VpnSymbol );

  if ( Element == (authelem *)0 )
  {
    if ( IsVasyDebugLevel1() )
    {
      VasyPrintf( stdout, "+ " );
    }

    VasySupportBit = addchain( VasySupportBit, VpnSymbol );
    addauthelem( VasyHashSupportBit, (char*)VpnSymbol, 0 );
  }
  else
  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "* " );
  }

  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "SupportBit <= %s %d\n", VpnSymbol->NAME, VpnSymbol->INDEX );
  }
}
