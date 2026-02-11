rebalance()
{
  imbprev = imbnow;
  itercount = balance->dynamic();


  if (fp) balance->dumpout(update->ntimestep,fp);


  comm->uniform = 0;


  if (domain->triclinic) domain->set_lamda_box();
  domain->set_local_box();


  if (domain->triclinic) domain->x2lamda(atom->nlocal);
  if (irregular->migrate_check()) irregular->migrate_atoms();
  if (domain->triclinic) domain->lamda2x(atom->nlocal);


  if (kspace_flag) force->kspace->setup_grid();


  pending = 1;
}
