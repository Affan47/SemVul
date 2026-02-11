lam_ssi_coll_lam_basic_barrier_inter(MPI_Comm intercomm)
{
  int local_rank;
  int err;
  MPI_Comm local_comm;

  local_comm = intercomm->c_ssi_coll_lam_basic_data->local_comm;


  MPI_Comm_rank(intercomm, &local_rank);


  lam_mkcoll(intercomm);


  if (MPI_Barrier(local_comm) != MPI_SUCCESS)
    return LAMERROR;


  if (local_rank == 0) {
    err = MPI_Sendrecv((void*) 0, 0, MPI_BYTE, 0, BLKMPIBARRIER,
		       (void*) 0, 0, MPI_BYTE, 0, BLKMPIBARRIER,
		       intercomm, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      lam_mkpt(intercomm);
      return err;
    }
  }


  if (MPI_Barrier(local_comm) != MPI_SUCCESS)
    return LAMERROR;

  lam_mkpt(intercomm);
  return (MPI_SUCCESS);
}
