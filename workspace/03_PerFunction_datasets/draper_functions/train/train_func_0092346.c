init()
{
    if (is_initialized)
        return;
    pthread_mutex_lock(&init_mutex);
    if (is_initialized)
    {
        pthread_mutex_unlock(&init_mutex);
        return;
    }

    LOADFUNC(execve);
    LOADFUNC(fexecve);
    LOADFUNC(execl);
    LOADFUNC(execlp);
    LOADFUNC(execle);
    LOADFUNC(execv);
    LOADFUNC(execvp);

    char* shm_name = getenv("HEXEC_EXPR_SHM");

    if(!shm_name)
        hexec_fatal("HEXEC_EXPR_SHM is not set\n");
    if(hexec_shm_open(&shm, shm_name))
        hexec_fatal("failed to map expression\n");
    if(hexec_shm_to_buf(&shm, &expr_buf))
    {
        hexec_shm_close(&shm);
        hexec_fatal("failed to get buf from shm\n");
    }

    expr_header = (struct hexec_expr_shm_header*)shm.buf;

    char* log_out_fd_str = getenv("HEXEC_LOG_FD");
    if(log_out_fd_str)
        log_out_fd = atoi(log_out_fd_str);

    is_initialized = 1;
    pthread_mutex_unlock(&init_mutex);
}
