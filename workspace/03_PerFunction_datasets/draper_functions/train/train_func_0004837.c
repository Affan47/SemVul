init_style()
{
  if (!atom->q_flag)
    error->all(FLERR,"Pair style cg/cut/coul/cut requires atom attribute q");

  PairCMMCommon::init_style();


  if (strstr(update->integrate_style,"respa") &&
      ((Respa *) update->integrate)->level_inner >= 0)
    cut_respa = ((Respa *) update->integrate)->cutoff;
  else cut_respa = NULL;
}
