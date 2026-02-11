SetSerialNum(OBAtom *atom, unsigned int sernum)
  {
    for ( unsigned int i = 0 ; i < _atoms.size() ; ++i )
      if (_atoms[i] == atom)
        _sernum[i] = sernum;
  }
