CheckAromaticity(OBAtom *atom,int depth)
  {
    OBAtom *nbr;
    vector<OBBond*>::iterator i;

    pair<int,int> erange;
    for (nbr = atom->BeginNbrAtom(i);nbr;nbr = atom->NextNbrAtom(i))
      if ((*i)->IsInRing())
        {
          erange = _velec[atom->GetIdx()];

          if (TraverseCycle(atom,nbr,(OBBond *)*i,erange,depth-1))
            {
              atom->SetAromatic();
              ((OBBond*) *i)->SetAromatic();
            }
        }
  }
