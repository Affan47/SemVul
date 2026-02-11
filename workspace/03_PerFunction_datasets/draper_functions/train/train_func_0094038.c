getNH(int atomNo) {
    int result=0;
    TSingleAtom * atom;
    int i,n;

    if (atomNo >= nAtoms()) return result;
    atom=getAtom(atomNo);
    result=atom->nv;
    result=result-(atom->currvalence)+(atom->nc*TSingleAtom::chargeDeltaValency(atom->na))-(atom->rl);
    if (result < 0) result=0;
    if (atom->nb > 0) for (i=0; i<atom->nb; i++) {
        n=atom->ac[i];
        if (getAtom(n)->na == 1) result=result+1;
      };
    return result;
  }
