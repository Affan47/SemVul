lam_ssi_coll_lam_basic_alltoallv_lamd(void *sbuf, int *scounts,
				      int *sdisps, MPI_Datatype sdtype,
				      void *rbuf, int *rcounts,
				      int *rdisps, MPI_Datatype rdtype,
				      MPI_Comm comm)
{
  int i;
  int size;
  int rank;
  int err;
  char *psnd;
  char *prcv;
  MPI_Aint sndextent;
  MPI_Aint rcvextent;


  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  MPI_Type_extent(sdtype, &sndextent);
  MPI_Type_extent(rdtype, &rcvextent);


  lam_mkcoll(comm);


  psnd = ((char *) sbuf) + (sdisps[rank] * sndextent);
  prcv = ((char *) rbuf) + (rdisps[rank] * rcvextent);
  err = lam_dtsndrcv(psnd, scounts[rank], sdtype,
		     prcv, rcounts[rank], rdtype, BLKMPIALLTOALLV, comm);
  if (err != MPI_SUCCESS) {
    lam_mkpt(comm);
    return err;
  }


  for (i = 0; i < size; ++i) {
    if (i == rank)
      continue;

    psnd = ((char *) sbuf) + (sdisps[i] * sndextent);
    prcv = ((char *) rbuf) + (rdisps[i] * rcvextent);
    err = MPI_Sendrecv(psnd, scounts[i], sdtype, i,
		       BLKMPIALLTOALLV, prcv, rcounts[i], rdtype, i,
		       BLKMPIALLTOALLV, comm, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      lam_mkpt(comm);
      return err;
    }
  }


  lam_mkpt(comm);
  return (MPI_SUCCESS);
}
