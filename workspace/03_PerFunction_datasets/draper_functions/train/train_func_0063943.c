shfree(void* ptr)
{
    int rc;

    RUNTIME_CHECK_INIT(); RUNTIME_CHECK_ADDR(ptr);

#if OSHMEM_SPEC_COMPAT == 1
    shmem_barrier_all();
#endif

    rc = MCA_MEMHEAP_CALL(free(ptr));
    if (OSHMEM_SUCCESS != rc) {
        SHMEM_API_VERBOSE(10, "shfree failure.");
    }
}
