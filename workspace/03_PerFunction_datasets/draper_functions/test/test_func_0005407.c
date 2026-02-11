jk_shm_lock()
{
    int rc = JK_TRUE;

    if (!jk_shm_inited_cs)
        return JK_FALSE;
    JK_ENTER_CS(&jk_shmem.cs);
#if defined (WIN32)
    if (jk_shm_hlock != NULL) {
        if (WaitForSingleObject(jk_shm_hlock, INFINITE) == WAIT_FAILED)
            rc = JK_FALSE;
    }
#else
    if (jk_shmem.fd_lock != -1) {
        JK_ENTER_LOCK(jk_shmem.fd_lock, rc);
    }
#endif
    return rc;
}
