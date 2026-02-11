DeleteHydrogens(OBAtom *atom)

  {
    OBAtom *nbr;
    vector<OBAtom*>::iterator i;
    vector<OBBond*>::iterator k;
    vector<OBAtom*> delatoms;

    for (nbr = atom->BeginNbrAtom(k);nbr;nbr = atom->NextNbrAtom(k))
      if (nbr->IsHydrogen())
        delatoms.push_back(nbr);

    if (delatoms.empty())
      return(true);

    IncrementMod();
    for (i = delatoms.begin();i != delatoms.end();++i)
      DeleteHydrogen((OBAtom*)*i);
    DecrementMod();

    UnsetHydrogensAdded();
    UnsetSSSRPerceived();
    return(true);
  }
