atoms()
{
  int i,m,nchunk,eof;

  bigint nread = 0;
  bigint natoms = atom->natoms;

  while (nread < natoms) {
    nchunk = MIN(natoms-nread,CHUNK);
    eof = comm->read_lines_from_file(fp,nchunk,MAXLINE,buffer);
    if (eof) error->all(FLERR,"Unexpected end of data file");
    atom->data_atoms(nchunk,buffer);
    nread += nchunk;
  }


  bigint tmp = atom->nlocal;
  MPI_Allreduce(&tmp,&natoms,1,MPI_LMP_BIGINT,MPI_SUM,world);

  if (me == 0) {
    if (screen) fprintf(screen,"  " BIGINT_FORMAT " atoms\n",natoms);
    if (logfile) fprintf(logfile,"  " BIGINT_FORMAT " atoms\n",natoms);
  }

  if (natoms != atom->natoms)
    error->all(FLERR,"Did not assign all atoms correctly");


  int nlocal = atom->nlocal;
  int *tag = atom->tag;

  int flag = 0;
  for (int i = 0; i < nlocal; i++)
    if (tag[i] < 0) flag = 1;
  int flag_all;
  MPI_Allreduce(&flag,&flag_all,1,MPI_INT,MPI_SUM,world);
  if (flag_all)
    error->all(FLERR,"Invalid atom ID in Atoms section of data file");

  flag = 0;
  for (int i = 0; i < nlocal; i++)
    if (tag[i] > 0) flag = 1;
  MPI_Allreduce(&flag,&flag_all,1,MPI_INT,MPI_MAX,world);
  if (flag_all == 0) atom->tag_enable = 0;

  if (atom->tag_enable) {
    flag = 0;
    for (int i = 0; i < nlocal; i++)
      if (tag[i] == 0) flag = 1;
    MPI_Allreduce(&flag,&flag_all,1,MPI_INT,MPI_SUM,world);
    if (flag_all)
      error->all(FLERR,"Invalid atom ID in Atoms section of data file");
  }


  if (atom->map_style) {
    atom->map_init();
    atom->map_set();
  }
}
