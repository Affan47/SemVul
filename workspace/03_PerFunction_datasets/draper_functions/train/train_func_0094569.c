compute_peratom()
{
  invoked_peratom = update->ntimestep;


  if (atom->nlocal > nmax) {
    memory->destroy(ke);
    nmax = atom->nmax;
    memory->create(ke,nmax,"ke/atom:ke");
    vector_atom = ke;
  }


  double mvv2e = force->mvv2e;
  double **v = atom->v;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int *mask = atom->mask;
  int *type = atom->type;
  int nlocal = atom->nlocal;

  if (rmass)
    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
        ke[i] = 0.5 * mvv2e * rmass[i] *
          (v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2]);
      } else ke[i] = 0.0;
    }

  else
    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
        ke[i] = 0.5 * mvv2e * mass[type[i]] *
          (v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2]);
      } else ke[i] = 0.0;
    }
}
