equivalenceList(const std::vector<int> aPosition,const std::vector<int> aCharge,
  const std::vector<int> aRad, const std::vector<int> iA1, const std::vector<int> iA2,
  const std::vector<int> bondTypes,  std::vector<int>& eqList, int nAtoms, int nBonds) {

  TEditedMolecule sm;
  TSingleAtom * sa;
  TSingleBond * sb;
  int i;

  sm.readConnectionMatrix(iA1,iA2,nAtoms,nBonds);
  for (i=0; i<sm.nAtoms(); i++) {
    sa=sm.getAtom(i);
    sa->na=aPosition[i];
    sa->nc=aCharge[i];
    sa->rl=aRad[i];
  };
  for (i=0; i<sm.nBonds(); i++) {
    sb=sm.getBond(i);
    sb->tb=bondTypes[i];
  };
  sm.defineAtomConn();
  sm.allAboutCycles();
  sm.makeEquivalentList(eqList,false);
}
