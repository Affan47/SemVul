init()
{
  int i,j;

  if (offset_flag && tail_flag)
    error->all(FLERR,"Cannot have both pair_modify shift and tail set to yes");
  if (tail_flag && domain->dimension == 2)
    error->all(FLERR,"Cannot use pair tail corrections with 2d simulations");
  if (tail_flag && domain->nonperiodic && comm->me == 0)
    error->warning(FLERR,"Using pair tail corrections with nonperiodic system");


  if (manybody_flag && atom->molecular) {
    int flag = 0;
    if (atom->nbonds > 0 && force->special_lj[1] == 0.0 &&
        force->special_coul[1] == 0.0) flag = 1;
    if (atom->nangles > 0 && force->special_lj[2] == 0.0 &&
        force->special_coul[2] == 0.0) flag = 1;
    if (atom->ndihedrals > 0 && force->special_lj[3] == 0.0 &&
        force->special_coul[3] == 0.0) flag = 1;
    if (flag && comm->me == 0)
      error->warning(FLERR,"Using a manybody potential with "
                     "bonds/angles/dihedrals and special_bond exclusions");
  }


  if (!allocated) error->all(FLERR,"All pair coeffs are not set");

  for (i = 1; i <= atom->ntypes; i++)
    if (setflag[i][i] == 0) error->all(FLERR,"All pair coeffs are not set");


  init_style();


  cutforce = 0.0;
  etail = ptail = 0.0;
  double cut;

  for (i = 1; i <= atom->ntypes; i++)
    for (j = i; j <= atom->ntypes; j++) {
      cut = init_one(i,j);
      cutsq[i][j] = cutsq[j][i] = cut*cut;
      cutforce = MAX(cutforce,cut);
      if (tail_flag) {
        etail += etail_ij;
        ptail += ptail_ij;
        if (i != j) {
          etail += etail_ij;
          ptail += ptail_ij;
        }
      }
    }
}
