RemoveAtom(OBAtom *atom)
  {
    if (atom != NULL && _atoms.size())
      {
        for ( unsigned int i = 0 ; i < _atoms.size() ; ++i)
          {
            if (_atoms[i] != NULL && _atoms[i] == atom)
              {
                atom->SetResidue(NULL);
                _atoms.erase(_atoms.begin() + i);
                _atomid.erase(_atomid.begin() + i);
                _hetatm.erase(_hetatm.begin() + i);
                _sernum.erase(_sernum.begin() + i);
              }
          }
      }
  }
