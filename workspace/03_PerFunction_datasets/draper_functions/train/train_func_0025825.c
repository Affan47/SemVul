read_restart(FILE *fp)
{
  allocate();

  if (comm->me == 0) {
    fread(&k[1],sizeof(double),atom->nbondtypes,fp);
    fread(&b1[1],sizeof(double),atom->nbondtypes,fp);
    fread(&b2[1],sizeof(double),atom->nbondtypes,fp);
    fread(&rc[1],sizeof(double),atom->nbondtypes,fp);
    fread(&u0[1],sizeof(double),atom->nbondtypes,fp);
  }
  MPI_Bcast(&k[1],atom->nbondtypes,MPI_DOUBLE,0,world);
  MPI_Bcast(&b1[1],atom->nbondtypes,MPI_DOUBLE,0,world);
  MPI_Bcast(&b2[1],atom->nbondtypes,MPI_DOUBLE,0,world);
  MPI_Bcast(&rc[1],atom->nbondtypes,MPI_DOUBLE,0,world);
  MPI_Bcast(&u0[1],atom->nbondtypes,MPI_DOUBLE,0,world);

  for (int i = 1; i <= atom->nbondtypes; i++) setflag[i] = 1;
}
