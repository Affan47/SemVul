read_restart_settings(FILE *fp)
{
  int me = comm->me;
  if (me == 0) {
    fread(&mix_flag,sizeof(int),1,fp);
  }
  MPI_Bcast(&mix_flag,1,MPI_INT,0,world);
}
