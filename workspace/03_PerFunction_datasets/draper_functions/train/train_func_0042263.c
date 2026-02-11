ompi_coll_tuned_barrier_intra_basic_linear(struct ompi_communicator_t *comm,
                                                      mca_coll_base_module_t *module)
{
    int i, err, rank, size;

    rank = ompi_comm_rank(comm);
    size = ompi_comm_size(comm);


    if (rank > 0) {
        err = MCA_PML_CALL(send (NULL, 0, MPI_BYTE, 0,
                                 MCA_COLL_BASE_TAG_BARRIER,
                                 MCA_PML_BASE_SEND_STANDARD, comm));
        if (MPI_SUCCESS != err) {
            return err;
        }

        err = MCA_PML_CALL(recv (NULL, 0, MPI_BYTE, 0,
                                 MCA_COLL_BASE_TAG_BARRIER,
                                 comm, MPI_STATUS_IGNORE));
        if (MPI_SUCCESS != err) {
            return err;
        }
    }


    else {
        ompi_request_t** requests;

        requests = (ompi_request_t**)malloc( size * sizeof(ompi_request_t*) );
        for (i = 1; i < size; ++i) {
            err = MCA_PML_CALL(irecv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE,
                                     MCA_COLL_BASE_TAG_BARRIER, comm,
                                     &(requests[i])));
            if (MPI_SUCCESS != err) {
                return err;
            }
        }
        ompi_request_wait_all( size-1, requests+1, MPI_STATUSES_IGNORE );

        for (i = 1; i < size; ++i) {
            err = MCA_PML_CALL(isend(NULL, 0, MPI_BYTE, i,
                                     MCA_COLL_BASE_TAG_BARRIER,
                                     MCA_PML_BASE_SEND_STANDARD, comm,
                                     &(requests[i])));
            if (MPI_SUCCESS != err) {
                return err;
            }
        }
        ompi_request_wait_all( size-1, requests+1, MPI_STATUSES_IGNORE );
        free( requests );
    }


    return MPI_SUCCESS;

}
