Clear()
  {
    vector<OBRotor*>::iterator i;
    for (i = _rotor.begin();i != _rotor.end();++i)
      delete *i;
    _rotor.clear();

  }
