init()
{
  int i,ibody;

  triclinic = domain->triclinic;


  int count = 0;
  for (i = 0; i < modify->nfix; i++)
    if (strcmp(modify->fix[i]->style,"rigid") == 0) count++;
  if (count > 1 && me == 0) error->warning(FLERR,"More than one fix rigid");


  for (i = 0; i < modify->nfix; i++) {
    if (strcmp(modify->fix[i]->style,"npt") == 0) break;
    if (strcmp(modify->fix[i]->style,"nph") == 0) break;
  }
  if (i < modify->nfix) {
    for (int j = i; j < modify->nfix; j++)
      if (strcmp(modify->fix[j]->style,"rigid") == 0)
        error->all(FLERR,"Rigid fix must come before NPT/NPH fix");
  }


  dtv = update->dt;
  dtf = 0.5 * update->dt * force->ftm2v;
  dtq = 0.5 * update->dt;

  if (strstr(update->integrate_style,"respa"))
    step_respa = ((Respa *) update->integrate)->step;
}
