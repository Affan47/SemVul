rme_shm_close(rme_shm_t *shm_data) {

    signed int unlink = 0;
    signed int lockfd;

    lockfd = rme_shm_lock_for_setup();

    rme_shm_lock(shm_data);
    shm_data->ref_count--;
    unlink = (shm_data->ref_count == 0);
    rme_shm_unlock(shm_data);

    if (unlink) {


        pthread_mutex_destroy(&shm_data->lock);
    }

    munmap(shm_data, RME_SHM_SIZE);

    if (unlink)
        shm_unlink(RME_SHM_NAME);

    rme_shm_unlock_for_setup(lockfd);

    return unlink?RSO_CLOSE_DELETE:RSO_CLOSE;
}
