init()
{


  if (regionflag) {
    iregion = domain->find_region(idregion);
    if (iregion == -1)
      error->all(FLERR,"Region ID for fix ave/spatial does not exist");
    region = domain->regions[iregion];
  }


  if (ave == RUNNING || ave == WINDOW) {
    if (scaleflag != REDUCED && domain->box_change_size)
      error->all(FLERR,
                 "Fix ave/spatial settings invalid with changing box size");
  }


  for (int m = 0; m < nvalues; m++) {
    if (which[m] == COMPUTE) {
      int icompute = modify->find_compute(ids[m]);
      if (icompute < 0)
        error->all(FLERR,"Compute ID for fix ave/spatial does not exist");
      value2index[m] = icompute;

    } else if (which[m] == FIX) {
      int ifix = modify->find_fix(ids[m]);
      if (ifix < 0)
        error->all(FLERR,"Fix ID for fix ave/spatial does not exist");
      value2index[m] = ifix;

      if (nevery % modify->fix[ifix]->peratom_freq)
        error->all(FLERR,
                   "Fix for fix ave/spatial not computed at compatible time");

    } else if (which[m] == VARIABLE) {
      int ivariable = input->variable->find(ids[m]);
      if (ivariable < 0)
        error->all(FLERR,"Variable name for fix ave/spatial does not exist");
      value2index[m] = ivariable;

    } else value2index[m] = -1;
  }


  if (nvalid < update->ntimestep) {
    irepeat = 0;
    nvalid = nextvalid();
    modify->addstep_compute_all(nvalid);
  }
}
