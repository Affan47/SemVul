GetExactMass(const unsigned int ele,
                                             const unsigned int isotope)
  {
    if (!_init)
      Init();

    if (ele > _isotopes.size())
      return 0.0;
    if (_isotopes[ele].size() == 0)
      return 0.0;

    unsigned int iso;
    for (iso = 0; iso < _isotopes[ele].size(); ++iso)
      if (isotope == _isotopes[ele][iso].first)
        return _isotopes[ele][iso].second;

    return 0.0;
  }
