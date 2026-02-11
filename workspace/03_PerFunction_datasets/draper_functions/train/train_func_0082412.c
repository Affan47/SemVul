compute_scalar()
{
  invoked_scalar = update->ntimestep;

  double **v = atom->v;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int *type = atom->type;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  double t = 0.0;

  if (rmass) {
    for (int i = 0; i < nlocal; i++)
      if (mask[i] & groupbit)
        t += (xflag*v[i][0]*v[i][0] + yflag*v[i][1]*v[i][1] +
              zflag*v[i][2]*v[i][2]) * rmass[i];
  } else {
    for (int i = 0; i < nlocal; i++)
      if (mask[i] & groupbit)
        t += (xflag*v[i][0]*v[i][0] + yflag*v[i][1]*v[i][1] +
              zflag*v[i][2]*v[i][2]) * mass[type[i]];
  }

  MPI_Allreduce(&t,&scalar,1,MPI_DOUBLE,MPI_SUM,world);
  if (dynamic) dof_compute();
  scalar *= tfactor;
  return scalar;
}
