mca_coll_basic_barrier_intra_log(struct ompi_communicator_t *comm,
                                 mca_coll_base_module_t *module)
{
    int i;
    int err;
    int peer;
    int dim;
    int hibit;
    int mask;
    int size = ompi_comm_size(comm);
    int rank = ompi_comm_rank(comm);


    dim = comm->c_cube_dim;
    hibit = opal_hibit(rank, dim);
    --dim;


    for (i = dim, mask = 1 << i; i > hibit; --i, mask >>= 1) {
        peer = rank | mask;
        if (peer < size) {
            err = MCA_PML_CALL(recv(NULL, 0, MPI_BYTE, peer,
                                    MCA_COLL_BASE_TAG_BARRIER,
                                    comm, MPI_STATUS_IGNORE));
            if (MPI_SUCCESS != err) {
                return err;
            }
        }
    }


    if (rank > 0) {
        peer = rank & ~(1 << hibit);
        err =
            MCA_PML_CALL(send
                         (NULL, 0, MPI_BYTE, peer,
                          MCA_COLL_BASE_TAG_BARRIER,
                          MCA_PML_BASE_SEND_STANDARD, comm));
        if (MPI_SUCCESS != err) {
            return err;
        }

        err = MCA_PML_CALL(recv(NULL, 0, MPI_BYTE, peer,
                                MCA_COLL_BASE_TAG_BARRIER,
                                comm, MPI_STATUS_IGNORE));
        if (MPI_SUCCESS != err) {
            return err;
        }
    }


    for (i = hibit + 1, mask = 1 << i; i <= dim; ++i, mask <<= 1) {
        peer = rank | mask;
        if (peer < size) {
            err = MCA_PML_CALL(send(NULL, 0, MPI_BYTE, peer,
                                    MCA_COLL_BASE_TAG_BARRIER,
                                    MCA_PML_BASE_SEND_STANDARD, comm));
            if (MPI_SUCCESS != err) {
                return err;
            }
        }
    }


    return MPI_SUCCESS;
}
