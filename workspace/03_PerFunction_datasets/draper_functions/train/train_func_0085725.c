loadvpnfig( Figure, Name, Reduced )

  vpnfig_list *Figure;
  char        *Name;
  int          Reduced;
{
  if ( ( VPN_IN == VPN_VHDL_FORMAT ) ||
       ( VPN_IN == VPN_SYN_FORMAT  ) ||
       ( VPN_IN == VPN_FSM_FORMAT  ) ||
       ( VPN_IN == VPN_VST_FORMAT  ) ||
       ( VPN_IN == VPN_VBE_FORMAT  ) )
  {
    vhdlloadvpnfig( Figure, Name, Reduced );
  }
  else
  if ( VPN_IN == VPN_VPN_FORMAT )
  {
    vpnloadvpnfig( Figure, Name );
  }
  else
  {
    vtlerror( VTL_UNKNOWN_VPN_IN, VPN_IN );
  }
}
