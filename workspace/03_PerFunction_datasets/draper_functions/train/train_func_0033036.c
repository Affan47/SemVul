GetInternalCoord()
  {
    if (_internals.empty())
      {
        _internals.push_back((OBInternalCoord*)NULL);
        for(unsigned int i = 1; i <= NumAtoms(); ++i)
          {
            _internals.push_back(new OBInternalCoord);
          }
        CartesianToInternal(_internals, *this);
      }
    return _internals;
  }
