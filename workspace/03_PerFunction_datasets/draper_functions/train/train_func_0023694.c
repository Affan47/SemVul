SteepestDescentInitialize(int steps, double econv, int method)
  {
    if (!_validSetup)
      return;

    _nsteps = steps;
    _cstep = 0;
    _econv = econv;

    if (_cutoff)
      UpdatePairsSimple();

    _e_n1 = Energy() + _constraints.GetConstraintEnergy();

    IF_OBFF_LOGLVL_LOW {
      OBFFLog("\nS T E E P E S T   D E S C E N T\n\n");
      snprintf(_logbuf, BUFF_SIZE, "STEPS = %d\n\n",  steps);
      OBFFLog(_logbuf);
      OBFFLog("STEP n       E(n)         E(n-1)    \n");
      OBFFLog("------------------------------------\n");
      snprintf(_logbuf, BUFF_SIZE, " %4d    %8.3f      ----\n", _cstep, _e_n1);
      OBFFLog(_logbuf);
    }

  }
