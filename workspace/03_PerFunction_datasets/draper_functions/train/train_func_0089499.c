oshmem_shmem_init(int argc, char **argv, int requested, int *provided)
{
    int ret = OSHMEM_SUCCESS;

    if (!oshmem_shmem_initialized) {
        if (!ompi_mpi_initialized && !ompi_mpi_finalized) {
            ret = ompi_mpi_init(argc, argv, requested, provided);
        }
        MPI_Comm_dup(MPI_COMM_WORLD, &oshmem_comm_world);

        if (OSHMEM_SUCCESS == ret) {
            ret = _shmem_init(argc, argv, requested, provided);
        }

        if (OSHMEM_SUCCESS == ret) {
            oshmem_shmem_initialized = true;


            MCA_MEMHEAP_CALL(get_all_mkeys());

            oshmem_shmem_preconnect_all();
#if OSHMEM_OPAL_THREAD_ENABLE
            pthread_t thread_id;
            int perr;
            perr = pthread_create(&thread_id, NULL, &shmem_opal_thread, NULL);
            if (perr != 0)
            {
                SHMEM_API_ERROR("cannot creat opal thread for SHMEM");
                return OSHMEM_ERROR;
            }
#endif
        }
    }
#ifdef SIGUSR1
    signal(SIGUSR1,sighandler__SIGUSR1);
    signal(SIGTERM,sighandler__SIGTERM);
#endif
    return ret;
}
