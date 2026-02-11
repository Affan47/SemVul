init()
{


  char **fixarg = new char*[3];
  fixarg[0] = (char *) "MINIMIZE";
  fixarg[1] = (char *) "all";
  fixarg[2] = (char *) "MINIMIZE";
  modify->add_fix(3,fixarg);
  delete [] fixarg;
  fix_minimize = (FixMinimize *) modify->fix[modify->nfix-1];


  nextra_global = 0;
  delete [] fextra;
  fextra = NULL;

  nextra_atom = 0;
  memory->sfree(xextra_atom);
  memory->sfree(fextra_atom);
  memory->destroy(extra_peratom);
  memory->destroy(extra_nlen);
  memory->destroy(extra_max);
  memory->sfree(requestor);
  xextra_atom = fextra_atom = NULL;
  extra_peratom = extra_nlen = NULL;
  extra_max = NULL;
  requestor = NULL;


  if (force->newton_pair) virial_style = 2;
  else virial_style = 1;


  ev_setup();


  int ifix = modify->find_fix("package_omp");
  if (ifix >= 0) external_force_clear = 1;


  torqueflag = 0;
  if (atom->torque_flag) torqueflag = 1;
  erforceflag = 0;
  if (atom->erforce_flag) erforceflag = 1;
  e_flag = 0;
  if (atom->e_flag) e_flag = 1;
  rho_flag = 0;
  if (atom->rho_flag) rho_flag = 1;


  if (force->pair && force->pair->compute_flag) pair_compute_flag = 1;
  else pair_compute_flag = 0;
  if (force->kspace && force->kspace->compute_flag) kspace_compute_flag = 1;
  else kspace_compute_flag = 0;


  triclinic = domain->triclinic;


  neigh_every = neighbor->every;
  neigh_delay = neighbor->delay;
  neigh_dist_check = neighbor->dist_check;

  if (neigh_every != 1 || neigh_delay != 0 || neigh_dist_check != 1) {
    if (comm->me == 0)
      error->warning(FLERR,
                     "Resetting reneighboring criteria during minimization");
  }

  neighbor->every = 1;
  neighbor->delay = 0;
  neighbor->dist_check = 1;

  niter = neval = 0;
}
