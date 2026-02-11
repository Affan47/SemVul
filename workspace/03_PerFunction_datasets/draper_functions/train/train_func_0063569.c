IsEster()
  {
    OBAtom *a1,*a2;
    a1 = a2 = NULL;

    if (_bgn->GetAtomicNum() == 6 && _end->GetAtomicNum() == 8)
      {
        a1 = (OBAtom*)_bgn;
        a2 = (OBAtom*)_end;
      }

    if (_bgn->GetAtomicNum() == 8 && _end->GetAtomicNum() == 6)
      {
        a1 = (OBAtom*)_end;
        a2 = (OBAtom*)_bgn;
      }

    if (!a1 || !a2)
      return(false);
    if (GetBO() != 1)
      return(false);

    OBBond *bond;
    vector<OBBond*>::iterator i;
    for (bond = a1->BeginBond(i);bond;bond = a1->NextBond(i))
      if (bond->IsCarbonyl())
        return(true);

    return(false);
  }
