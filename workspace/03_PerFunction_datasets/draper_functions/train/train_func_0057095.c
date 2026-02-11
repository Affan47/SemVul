bonds()
{
  int i,m,nchunk,eof;

  bigint nread = 0;
  bigint nbonds = atom->nbonds;

  bigint natoms = atom->natoms;

  while (nread < nbonds) {
    nchunk = MIN(nbonds-nread,CHUNK);
    eof = comm->read_lines_from_file(fp,nchunk,MAXLINE,buffer);
    if (eof) error->all(FLERR,"Unexpected end of data file");
    atom->data_bonds(nchunk,buffer);
    nread += nchunk;
  }


  int nlocal = atom->nlocal;
  bigint sum;
  bigint n = 0;
  for (i = 0; i < nlocal; i++) n += atom->num_bond[i];
  MPI_Allreduce(&n,&sum,1,MPI_LMP_BIGINT,MPI_SUM,world);
  int factor = 1;
  if (!force->newton_bond) factor = 2;

  if (me == 0) {
    if (screen) fprintf(screen,"  " BIGINT_FORMAT " bonds\n",sum/factor);
    if (logfile) fprintf(logfile,"  " BIGINT_FORMAT " bonds\n",sum/factor);
  }
  if (sum != factor*atom->nbonds)
    error->all(FLERR,"Bonds assigned incorrectly");
}
