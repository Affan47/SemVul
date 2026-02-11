destroy(void)
{
    int i;
    pthread_mutex_lock(&lock);
    for(i = 0; i < max_fds; i++) {
        if(fds[i].fd == -1)
            continue;
        if(!valid_fd(fds[i].fd))
            continue;
        pthread_mutex_unlock(&lock);
        free_unclaimed_pages(fds[i].fd);
        pthread_mutex_lock(&lock);
    }
    pthread_mutex_unlock(&lock);
    free(fds);
}
