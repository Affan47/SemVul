compute_scalar()
{
  invoked_scalar = update->ntimestep;

  double **x = atom->x;
  double **v = atom->v;
  double *ervel = atom->ervel;
  double *mass = atom->mass;
  int *spin = atom->spin;
  int *type = atom->type;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;
  double mefactor = domain->dimension/4.0;

  Region *region = domain->regions[iregion];
  int count = 0;
  int ecount = 0;
  double t = 0.0;

  if (mass) {
    for (int i = 0; i < nlocal; i++)
      if (mask[i] & groupbit && region->match(x[i][0],x[i][1],x[i][2])) {
        count++;
        t += (v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2]) *
          mass[type[i]];
        if (fabs(spin[i])==1) {
          t += mefactor*mass[type[i]]*ervel[i]*ervel[i];
          ecount++;
        }
      }
  }

  double tarray[2],tarray_all[2];

  tarray[0] = count-ecount;
  tarray[1] = t;
  MPI_Allreduce(tarray,tarray_all,2,MPI_DOUBLE,MPI_SUM,world);
  dof = domain->dimension * tarray_all[0] - extra_dof;

  int one = 0;
  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit && region->match(x[i][0],x[i][1],x[i][2])) {
      if (fabs(spin[i])==1) one++;
    }

  if (dof > 0) scalar = force->mvv2e * tarray_all[1] / (dof * force->boltz);
  else scalar = 0.0;
  return scalar;
}
