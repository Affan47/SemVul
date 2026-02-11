ompi_coll_tuned_alltoallv_intra_do_forced(void *sbuf, int *scounts, int *sdisps,
                                              struct ompi_datatype_t *sdtype,
                                              void* rbuf, int *rcounts, int *rdisps,
                                              struct ompi_datatype_t *rdtype,
                                              struct ompi_communicator_t *comm,
                                              mca_coll_base_module_t *module)
{
    mca_coll_tuned_module_t *tuned_module = (mca_coll_tuned_module_t*) module;
    mca_coll_tuned_comm_t *data = tuned_module->tuned_data;

    OPAL_OUTPUT((ompi_coll_tuned_stream,
                 "coll:tuned:alltoallv_intra_do_forced selected algorithm %d",
                 data->user_forced[ALLTOALLV].algorithm));

    switch (data->user_forced[ALLTOALLV].algorithm) {
    case (0):
        return ompi_coll_tuned_alltoallv_intra_dec_fixed(sbuf, scounts, sdisps, sdtype,
                                                         rbuf, rcounts, rdisps, rdtype,
                                                         comm, module);
    case (1):
        return ompi_coll_tuned_alltoallv_intra_basic_linear(sbuf, scounts, sdisps, sdtype,
                                                            rbuf, rcounts, rdisps, rdtype,
                                                            comm, module);
    case (2):
        return ompi_coll_tuned_alltoallv_intra_pairwise(sbuf, scounts, sdisps, sdtype,
                                                        rbuf, rcounts, rdisps, rdtype,
                                                        comm, module);
    default:
        OPAL_OUTPUT((ompi_coll_tuned_stream,
                     "coll:tuned:alltoallv_intra_do_forced attempt to "
                     "select algorithm %d when only 0-%d is valid.",
                     data->user_forced[ALLTOALLV].algorithm,
                     ompi_coll_tuned_forced_max_algorithms[ALLTOALLV]));
        return (MPI_ERR_ARG);
    }
}
