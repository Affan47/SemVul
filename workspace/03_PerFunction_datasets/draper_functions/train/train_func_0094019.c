readConnectionMatrix(const std::vector<int>iA1, const std::vector<int>iA2, int nAtoms, int nBonds) {
    TSingleAtom * sa;
    TSingleBond * sb;
    int i;

    clear();
    srand(30000);
    for (i=1; i<=nAtoms; i++) {
      sa=new TSingleAtom();
      sa->na=6;
      sa->nv=hVal[sa->na];
      sa->rx=(double)rand()/1000.0;
      sa->ry=(double)rand()/1000.0;
      fAtom.push_back(sa);
    };

    for (i=0; i<nBonds; i++) {
      sb=new TSingleBond();
      sb->at[0]=iA1[i];
      sb->at[1]=iA2[i];
      sb->tb=1;
      fBond.push_back(sb);
    };
    defineAtomConn();
    allAboutCycles();
  }
