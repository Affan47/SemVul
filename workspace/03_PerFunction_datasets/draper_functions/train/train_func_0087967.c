SystematicRotorSearchInitialize(unsigned int geomSteps)
  {
    if (!_validSetup)
      return 0;

    OBRotorList rl;
    OBRotamerList rotamers;
    OBRotorIterator ri;
    OBRotor *rotor;

    _origLogLevel = _loglvl;

    OBBitVec fixed = _constraints.GetFixedBitVec();
    rl.SetFixAtoms(fixed);
    rl.Setup(_mol);
    rotamers.SetBaseCoordinateSets(_mol);
    rotamers.Setup(_mol, rl);

    IF_OBFF_LOGLVL_LOW {
      OBFFLog("\nS Y S T E M A T I C   R O T O R   S E A R C H\n\n");
      snprintf(_logbuf, BUFF_SIZE, "  NUMBER OF ROTATABLE BONDS: %lu\n", (unsigned long)rl.Size());
      OBFFLog(_logbuf);

      unsigned long int combinations = 1;
      for (rotor = rl.BeginRotor(ri); rotor;
           rotor = rl.NextRotor(ri)) {
        combinations *= rotor->GetResolution().size();
      }
      snprintf(_logbuf, BUFF_SIZE, "  NUMBER OF POSSIBLE ROTAMERS: %lu\n", combinations);
      OBFFLog(_logbuf);
    }

    if (!rl.Size()) {
      IF_OBFF_LOGLVL_LOW
        OBFFLog("  GENERATED ONLY ONE CONFORMER\n\n");

      ConjugateGradients(geomSteps);

      return 1;
    }

    OBRotorKeys rotorKeys;
    rotor = rl.BeginRotor(ri);
    for (int i = 1; i < rl.Size() + 1; ++i, rotor = rl.NextRotor(ri))
      rotorKeys.AddRotor(rotor->GetResolution().size());

    rotamers.AddRotamer(rotorKeys.GetKey());
    while (rotorKeys.Next())
      rotamers.AddRotamer(rotorKeys.GetKey());

    rotamers.ExpandConformerList(_mol, _mol.GetConformers());

    IF_OBFF_LOGLVL_LOW {
      snprintf(_logbuf, BUFF_SIZE, "  GENERATED %d CONFORMERS\n\n", _mol.NumConformers());
      OBFFLog(_logbuf);
      OBFFLog("CONFORMER     ENERGY\n");
      OBFFLog("--------------------\n");
    }

    _current_conformer = 0;
    _energies.clear();

    return _mol.NumConformers();
  }
