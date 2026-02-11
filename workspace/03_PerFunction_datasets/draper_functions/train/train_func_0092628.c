IsPolarHydrogen()
  {
    if (!IsHydrogen())
      return(false);

    OBAtom *atom;
    OBBond *bond;
    OBBondIterator i;
    for (bond = BeginBond(i);bond;bond = NextBond(i))
      {
        atom = bond->GetNbrAtom(this);
        if (atom->GetAtomicNum() == 7)
          return(true);
        if (atom->GetAtomicNum() == 8)
          return(true);
        if (atom->GetAtomicNum() == 15)
          return(true);
        if (atom->GetAtomicNum() == 16)
          return(true);
      }

    return(false);
  }
