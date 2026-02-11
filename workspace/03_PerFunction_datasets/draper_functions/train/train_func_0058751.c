VasyRedActAddVpnDefine( VpnFigure, VpnProc, Width, DefBase )

  vpnfig_list    *VpnFigure;
  vpnproc_list   *VpnProc;
  unsigned short  Width;
  unsigned char   DefBase;
{
  vpndecl_list *DefDeclar;
  vexexpr      *DefAtom;
  char         *FatherName;
  char          Buffer[ 128 ];
  unsigned char NewBase;
  long          Number;

  FatherName = VpnProc->NAME;
  Number     = GetVpnNumDeclDef( VpnFigure );

  sprintf( Buffer, "%s_reddef_%ld", FatherName, Number );

  if ( ( DefBase == VEX_TYPE_REG_BIT ) ||
       ( DefBase == VEX_TYPE_MUX_BIT ) ||
       ( DefBase == VEX_TYPE_WOR_BIT ) )
  {
    DefBase = VEX_TYPE_BIT;
  }
  else
  if ( ( DefBase == VEX_TYPE_REG_VECTOR ) ||
       ( DefBase == VEX_TYPE_MUX_VECTOR ) ||
       ( DefBase == VEX_TYPE_WOR_VECTOR ) )
  {
    DefBase = VEX_TYPE_BIT_VECTOR;
  }

  NewBase = getvextypescalar( DefBase );

  if ( ( isvextypevector( DefBase ) ) &&
       ( ( Width   >  1           ) ||
         ( NewBase == DefBase     ) ) )
  {
    DefAtom = createvexatomvec( Buffer, Width - 1, 0 );
  }
  else
  {
    DefAtom = createvexatombit( Buffer );
    DefBase = NewBase;
  }

  DefDeclar = addvpndeclprocdef( VpnFigure, VpnProc, DefAtom, DefBase );

  return( DefDeclar );
}
