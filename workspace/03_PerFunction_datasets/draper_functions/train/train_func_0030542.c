IsChiral()
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator i;

    for (atom = BeginAtom(i);atom;atom = NextAtom(i))
      if ((atom->IsCarbon() || atom->IsNitrogen()) && atom->GetHvyValence() > 2 && atom->IsChiral())
        return(true);

    return(false);
  }
