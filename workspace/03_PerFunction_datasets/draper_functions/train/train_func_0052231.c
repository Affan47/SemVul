mca_scoll_mpi_barrier(struct oshmem_group_t *group, long *pSync, int alg)
{
    mca_scoll_mpi_module_t *mpi_module;
    int rc;
    MPI_COLL_VERBOSE(20,"RUNNING MPI BARRIER");
    mpi_module = (mca_scoll_mpi_module_t *) group->g_scoll.scoll_barrier_module;

    rc = mpi_module->comm->c_coll.coll_barrier(mpi_module->comm, mpi_module->comm->c_coll.coll_barrier_module);
    if (OMPI_SUCCESS != rc){
        MPI_COLL_VERBOSE(20,"RUNNING FALLBACK BARRIER");
        PREVIOUS_SCOLL_FN(mpi_module, barrier, group,
                pSync,
                SCOLL_DEFAULT_ALG);
    }
    return rc;
}
