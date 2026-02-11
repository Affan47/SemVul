IsAmideNitrogen()
  {
    if (!IsNitrogen())
      return(false);

    OBAtom *nbratom,*atom;
    OBBond *abbond,*bond;

    OBBondIterator i,j;
    atom = this;
    for (bond = BeginBond(i);bond;bond = NextBond(i))
      {
        nbratom = bond->GetNbrAtom(atom);
        for (abbond = nbratom->BeginBond(j);abbond;abbond = nbratom->NextBond(j))
          if (abbond->GetBO() == 2 &&
              (((abbond->GetNbrAtom(nbratom))->GetAtomicNum() == 8) ||
               ((abbond->GetNbrAtom(nbratom))->GetAtomicNum() == 16)))
            return(true);
      }

    return(false);
  }
