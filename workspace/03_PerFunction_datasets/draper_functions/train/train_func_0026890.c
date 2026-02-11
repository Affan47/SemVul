charge(int igroup)
{
  int groupbit = bitmask[igroup];

  double *q = atom->q;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  double qone = 0.0;
  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) qone += q[i];

  double qall;
  MPI_Allreduce(&qone,&qall,1,MPI_DOUBLE,MPI_SUM,world);
  return qall;
}
