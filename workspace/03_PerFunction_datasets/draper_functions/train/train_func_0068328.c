read_restart_settings(FILE *fp)
{
  if (comm->me == 0) {
    fread(&kn,sizeof(double),1,fp);
    fread(&kt,sizeof(double),1,fp);
    fread(&gamman,sizeof(double),1,fp);
    fread(&gammat,sizeof(double),1,fp);
    fread(&xmu,sizeof(double),1,fp);
    fread(&dampflag,sizeof(int),1,fp);
  }
  MPI_Bcast(&kn,1,MPI_DOUBLE,0,world);
  MPI_Bcast(&kt,1,MPI_DOUBLE,0,world);
  MPI_Bcast(&gamman,1,MPI_DOUBLE,0,world);
  MPI_Bcast(&gammat,1,MPI_DOUBLE,0,world);
  MPI_Bcast(&xmu,1,MPI_DOUBLE,0,world);
  MPI_Bcast(&dampflag,1,MPI_INT,0,world);
}
