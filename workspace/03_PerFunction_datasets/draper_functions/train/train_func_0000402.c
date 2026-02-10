lam_ssi_coll_lam_basic_allreduce_inter(void *sbuf, void *rbuf, int count,
				       MPI_Datatype dtype, MPI_Op op,
				       MPI_Comm intercomm)
{
  int local_rank, root;
  MPI_Comm local_comm;
  int is_low;

  local_comm = intercomm->c_ssi_coll_lam_basic_data->local_comm;
  is_low = intercomm->c_ssi_coll_lam_basic_data->is_low;


  MPI_Comm_rank(intercomm, &local_rank);
  if (is_low) {

    root = (local_rank == 0) ? MPI_ROOT : MPI_PROC_NULL;
    if (MPI_Reduce(sbuf, rbuf, count, dtype, op, root, intercomm)
	!= MPI_SUCCESS) {
      return LAMERROR;
    }
    root = 0;
    if (MPI_Reduce(sbuf, rbuf, count, dtype, op, root, intercomm)
	!= MPI_SUCCESS) {
      return LAMERROR;
    }
  } else {

    root = 0;
    if (MPI_Reduce(sbuf, rbuf, count, dtype, op, root, intercomm)
	!= MPI_SUCCESS) {
      return LAMERROR;
    }

    root = (local_rank == 0) ? MPI_ROOT : MPI_PROC_NULL;
    if (MPI_Reduce(sbuf, rbuf, count, dtype, op, root, intercomm)
	!= MPI_SUCCESS) {
      return LAMERROR;
    }
  }


  if ((MPI_Bcast(rbuf, count, dtype, 0, local_comm)) != MPI_SUCCESS) {
    return LAMERROR;
  }

  return MPI_SUCCESS;
}
