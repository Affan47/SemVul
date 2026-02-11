GetSerialNum(OBAtom *atom) const
  {
    for ( unsigned int i = 0 ; i < _atoms.size() ; ++i )
      if (_atoms[i] == atom)
        return _sernum[i];
    return 0;
  }
