PropagatePotentialAromatic(OBAtom *atom)
  {
    int count = 0;
    OBAtom *nbr;
    vector<OBBond*>::iterator i;

    for (nbr = atom->BeginNbrAtom(i);nbr;nbr = atom->NextNbrAtom(i))
      if ((*i)->IsInRing() && _vpa[nbr->GetIdx()])
        count++;

    if (count < 2)
      {
        _vpa[atom->GetIdx()] = false;
        if (count == 1)
          for (nbr = atom->BeginNbrAtom(i);nbr;nbr = atom->NextNbrAtom(i))
            if ((*i)->IsInRing() && _vpa[nbr->GetIdx()])
              PropagatePotentialAromatic(nbr);
      }
  }
