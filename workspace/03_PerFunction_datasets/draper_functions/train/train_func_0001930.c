KBOSum() const
  {
    OBBond *bond;
    unsigned int bosum;
    OBBondIterator i;

    bosum = GetImplicitValence();

    for (bond = ((OBAtom*)this)->BeginBond(i);bond;bond = ((OBAtom*)this)->NextBond(i))
      {
        if (bond->IsKDouble())
          bosum++;
        else if (bond->IsKTriple())
          bosum += 2;
      }

    return(bosum);
  }
