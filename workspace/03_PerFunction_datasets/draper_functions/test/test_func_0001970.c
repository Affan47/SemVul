lam_ssi_coll_lam_basic_barrier_log(MPI_Comm comm)
{
  int size;
  int rank;
  int peer;
  int dim;
  int hibit;
  int mask;
  int err;
  int i;


  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  lam_mkcoll(comm);
  dim = comm->c_cube_dim;
  hibit = lam_hibit(rank, dim);
  --dim;


  for (i = dim, mask = 1 << i; i > hibit; --i, mask >>= 1) {
    peer = rank | mask;
    if (peer < size) {
      err = MPI_Recv((void *) 0, 0, MPI_BYTE,
		     peer, BLKMPIBARRIER, comm, MPI_STATUS_IGNORE);
      if (err != MPI_SUCCESS) {
	lam_mkpt(comm);
	return err;
      }
    }
  }


  if (rank > 0) {
    peer = rank & ~(1 << hibit);
    err = MPI_Send((void *) 0, 0, MPI_BYTE, peer, BLKMPIBARRIER, comm);
    if (err != MPI_SUCCESS) {
      lam_mkpt(comm);
      return err;
    }

    err = MPI_Recv((void *) 0, 0, MPI_BYTE, peer,
		   BLKMPIBARRIER, comm, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      lam_mkpt(comm);
      return err;
    }
  }


  for (i = hibit + 1, mask = 1 << i; i <= dim; ++i, mask <<= 1) {
    peer = rank | mask;
    if (peer < size) {
      err = MPI_Send((void *) 0, 0, MPI_BYTE, peer, BLKMPIBARRIER, comm);
      if (err != MPI_SUCCESS) {
	lam_mkpt(comm);
	return err;
      }
    }
  }

  lam_mkpt(comm);
  return (MPI_SUCCESS);
}
