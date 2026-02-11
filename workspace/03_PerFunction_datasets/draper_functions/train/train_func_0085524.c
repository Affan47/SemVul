spher_harm(EnvT* e)
  {

    SizeT nParam=e->NParam(4);

    BaseGDL *theta = e->GetNumericParDefined(0);
    BaseGDL *phi = e->GetNumericParDefined(1);

    int step_theta = 1, step_phi = 1;
    SizeT length = theta->N_Elements();
    if (theta->N_Elements() != phi->N_Elements())
      {
	if (
	    (theta->N_Elements() > 1 && phi->Rank() != 0) ||
	    (phi->N_Elements() > 1 && theta->Rank() != 0)
	    ) e->Throw("Theta (1st arg.) or Phi (2nd arg.) must be scalar, or have the same number of values");
	if (theta->N_Elements() > 1) step_phi = 0;
	else
	  {
	    step_theta = 0;
	    length = phi->N_Elements();
	  }
      }

    DLong l;
    e->AssureLongScalarPar(2, l);
    if (l < 0) e->Throw("L (3rd arg.) must be greater than or equal to zero");

    DLong m;
    e->AssureLongScalarPar(3, m);
    if (abs(m) > l) e->Throw("M (4th arg.) must be in the range [-L, L]");


    BaseGDL *res;
    bool dbl = e->KeywordSet(0) || theta->Type() == GDL_DOUBLE || phi->Type() == GDL_DOUBLE;
    {
      dimension dim = dimension(length);
      if (phi->Rank() == 0 && theta->Rank() == 0) dim.Remove(0);
      if (dbl) res = new DComplexDblGDL(dim);
      else res = new DComplexGDL(dim);
    }
    Guard<BaseGDL> res_guard(res);


    if (dbl)
      spher_harm_helper(e, theta, phi, &((*static_cast<DComplexDblGDL*>(res))[0]), l, m, step_theta, step_phi, length);
    else
      spher_harm_helper(e, theta, phi, &((*static_cast<DComplexGDL*>(res))[0]), l, m, step_theta, step_phi, length);


    res_guard.release();
    return res;
  }
