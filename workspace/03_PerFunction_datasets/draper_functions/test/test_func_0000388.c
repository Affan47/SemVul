VasyVexBddAddBddCircuitInput( VpnFigure, VpnProc, VpnSymbol )

  vpnfig_list  *VpnFigure;
  vpnproc_list *VpnProc;
  vpnsym       *VpnSymbol;
{
  vasyprocinfo *ProcInfo;
  bddcircuit  *BddCircuit;
  bddnode     *BddNode;
  char        *AblName;
  char        *DelName;

  ProcInfo   = GetVasyVpnProcInfo( VpnProc );
  BddCircuit = ProcInfo->BDD_CIRCUIT;

  VasyHashSym2Abl = ProcInfo->HASH_SYM2ABL;
  VasyHashAbl2Sym = ProcInfo->HASH_ABL2SYM;

  AblName = VasyVexBddGetAblName( VpnSymbol );
  DelName = VasyVexBddGetAblDelName( AblName );

  BddNode = searchbddcircuitin( BddCircuit, DelName );

  if ( BddNode == (bddnode *)0 )
  {
    BddNode = addbddcircuitin( BddCircuit, AblName, 0, BDD_IN_MODE_LAST );
  }
  else
  {
    BddNode = renamebddcircuitin( BddCircuit, DelName, AblName );
  }

  return( BddNode );
}
