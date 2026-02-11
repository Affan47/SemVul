lam_ssi_coll_smp_reduce(void *sbuf, void *rbuf, int count,
			MPI_Datatype dtype, MPI_Op op,
			int root, MPI_Comm comm)
{
  lam_ssi_coll_data_t *lcd = comm->c_ssi_coll_data;


  if (lam_ssi_coll_base_get_param(comm, LAM_MPI_SSI_COLL_ASSOCIATIVE) == 1 &&
      op->op_commute)
    return assoc_reduce(sbuf, rbuf, count, dtype, op, root, comm);


  return lcd->lb_functions.lsca_reduce(sbuf, rbuf, count, dtype,
                                       op, root, comm);
}
