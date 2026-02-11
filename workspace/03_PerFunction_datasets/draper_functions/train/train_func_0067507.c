SteepestDescentTakeNSteps(int n)
  {
    if (!_validSetup)
      return 0;

    int _ncoords = _mol.NumAtoms() * 3;
    double e_n2, alpha;
    vector3 dir;

    for (int i = 1; i <= n; i++) {
      _cstep++;

      FOR_ATOMS_OF_MOL (a, _mol) {
        unsigned int idx = a->GetIdx();
        unsigned int coordIdx = (idx - 1) * 3;

        if (_constraints.IsFixed(idx) || (_fixAtom == idx) || (_ignoreAtom == idx)) {
          _gradientPtr[coordIdx] = 0.0;
          _gradientPtr[coordIdx+1] = 0.0;
          _gradientPtr[coordIdx+2] = 0.0;
        } else {
          if (!HasAnalyticalGradients()) {

            dir = NumericalDerivative(&*a) + _constraints.GetGradient(a->GetIdx());
          } else {

            dir = GetGradient(&*a) + _constraints.GetGradient(a->GetIdx());
          }

          if (!_constraints.IsXFixed(idx))
            _gradientPtr[coordIdx] = dir.x();
          else
            _gradientPtr[coordIdx] = 0.0;

          if (!_constraints.IsYFixed(idx))
            _gradientPtr[coordIdx+1] = dir.y();
          else
            _gradientPtr[coordIdx+1] = 0.0;

          if (!_constraints.IsZFixed(idx))
            _gradientPtr[coordIdx+2] = dir.z();
          else
            _gradientPtr[coordIdx+2] = 0.0;
        }
      }

      switch (_linesearch) {
      case LineSearchType::Newton2Num:
        alpha = Newton2NumLineSearch(_gradientPtr);
        break;
      default:
      case LineSearchType::Simple:
        alpha = LineSearch(_mol.GetCoordinates(), _gradientPtr);
        break;
      }
      e_n2 = Energy() + _constraints.GetConstraintEnergy();

      if ((_cstep % _pairfreq == 0) && _cutoff)
        UpdatePairsSimple();

      IF_OBFF_LOGLVL_LOW {
        if (_cstep % 10 == 0) {
          snprintf(_logbuf, BUFF_SIZE, " %4d    %8.5f    %8.5f\n", _cstep, e_n2, _e_n1);
          OBFFLog(_logbuf);
        }
      }

      if (IsNear(e_n2, _e_n1, _econv)) {
        IF_OBFF_LOGLVL_LOW
          OBFFLog("    STEEPEST DESCENT HAS CONVERGED\n");
        return false;
      }

      if (_nsteps == _cstep) {
        return false;
      }

      _e_n1 = e_n2;
    }

    return true;
  }
