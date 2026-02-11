deleteAtom(int index) {
  std::vector<TSingleAtom*> tempAtom(nAtoms()-1);
  std::vector<TSingleBond*> tempBond(nBonds());
  int i,n;

  n=0;

  for (i=0; i<nAtoms(); i++) if (i != index) {
    tempAtom[n]=getAtom(i);
    n++;
  } else {
    delete(getAtom(i));
    fAtom[i]=NULL;
  };
  fAtom.resize(n);
  for (i=0; i<n; i++) fAtom[i]=tempAtom[i];
  tempAtom.clear();

  n=0;
  for (i=0; i<tempBond.size(); i++) {
    if ((getBond(i)->at[0] == index) || (getBond(i)->at[1] == index)) {
      delete(getBond(i));
      fBond[i]=NULL;
    } else {
      if (getBond(i)->at[0] > index) getBond(i)->at[0]=getBond(i)->at[0]-1;
      if (getBond(i)->at[1] > index) getBond(i)->at[1]=getBond(i)->at[1]-1;
      tempBond[n]=getBond(i);
      n++;
    };
  };
  fBond.resize(n);
  for (i=0; i<n; i++) fBond[i]=tempBond[i];
  tempBond.clear();
}
