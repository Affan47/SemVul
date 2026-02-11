bcast_table(Table *tb)
{
  MPI_Bcast(&tb->ninput,1,MPI_INT,0,world);

  int me;
  MPI_Comm_rank(world,&me);
  if (me > 0) {
    memory->create(tb->phifile,tb->ninput,"dihedral:phifile");
    memory->create(tb->efile,tb->ninput,"dihedral:efile");
    memory->create(tb->ffile,tb->ninput,"dihedral:ffile");
  }

  MPI_Bcast(tb->phifile,tb->ninput,MPI_DOUBLE,0,world);
  MPI_Bcast(tb->efile,tb->ninput,MPI_DOUBLE,0,world);
  MPI_Bcast(tb->ffile,tb->ninput,MPI_DOUBLE,0,world);

  MPI_Bcast(&tb->f_unspecified,1,MPI_INT,0,world);
  MPI_Bcast(&tb->use_degrees,1,MPI_INT,0,world);


}
