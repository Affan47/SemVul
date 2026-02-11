mca_coll_inter_bcast_inter(void *buff, int count,
                           struct ompi_datatype_t *datatype, int root,
                           struct ompi_communicator_t *comm,
                           mca_coll_base_module_t *module)
{
    int rank;
    int err;

    rank = ompi_comm_rank(comm);

    if (MPI_PROC_NULL == root) {

        err = OMPI_SUCCESS;
    } else if (MPI_ROOT != root) {

	if ( 0 == rank ) {
	    err = MCA_PML_CALL(recv(buff, count, datatype, root,
				    MCA_COLL_BASE_TAG_BCAST, comm,
				    MPI_STATUS_IGNORE));
	    if (OMPI_SUCCESS != err) {
                return err;
            }
	}
	err = comm->c_local_comm->c_coll.coll_bcast(buff, count, datatype, 0,
                                                    comm->c_local_comm,
                                                    comm->c_local_comm->c_coll.coll_bcast_module);
    } else {

	err = MCA_PML_CALL(send(buff, count, datatype, 0,
				MCA_COLL_BASE_TAG_BCAST,
				MCA_PML_BASE_SEND_STANDARD,
				comm));
	if (OMPI_SUCCESS != err) {
	    return err;
	}
    }


    return err;
}
