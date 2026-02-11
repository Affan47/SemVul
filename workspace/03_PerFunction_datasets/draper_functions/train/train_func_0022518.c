compute_fmax()
{
  double **f = atom->f;
  int nlocal = atom->nlocal;

  double max = 0.0;
  for (int i = 0; i < nlocal; i++) {
    max = MAX(max,fabs(f[i][0]));
    max = MAX(max,fabs(f[i][1]));
    max = MAX(max,fabs(f[i][2]));
  }
  double maxall;
  MPI_Allreduce(&max,&maxall,1,MPI_DOUBLE,MPI_MAX,world);
  dvalue = maxall;
}
