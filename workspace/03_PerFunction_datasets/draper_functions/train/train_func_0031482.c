NumHvyAtoms()
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator(i);
    unsigned int count = 0;

    for(atom = this->BeginAtom(i);atom;atom = this->NextAtom(i))
      {
        if(!atom->IsHydrogen())
          count++;
      }

    return(count);
  }
