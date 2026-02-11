init()
{
  fix_dof = 0;
  for (int i = 0; i < modify->nfix; i++)
    fix_dof += modify->fix[i]->dof(igroup);
  dof_compute();


  box_change = domain->box_change;
  triclinic = domain->triclinic;
  periodicity = domain->periodicity;

  if (triclinic) {
    boxlo = domain->boxlo_lamda;
    boxhi = domain->boxhi_lamda;
    prd = domain->prd_lamda;
  } else {
    boxlo = domain->boxlo;
    boxhi = domain->boxhi;
    prd = domain->prd;
  }

  if (!box_change) bin_setup();
}
