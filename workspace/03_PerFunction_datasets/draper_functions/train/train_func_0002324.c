clear() {
    for (unsigned int i=0; i<fAtom.size(); i++) delete(fAtom.at(i));
    fAtom.clear();
    for (unsigned int i=0; i<fBond.size(); i++) delete(fBond.at(i));
    fBond.clear();
  }
