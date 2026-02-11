init_threads()
{
    struct sigaction sa_terminate;
    sigset_t sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGHUP);
    sigaddset(&sigmask, SIGQUIT);
    sigaddset(&sigmask, SIGINT);
    sigaddset(&sigmask, SIGTERM);

    pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
    sa_terminate.sa_handler = terminate;

    sa_terminate.sa_mask = sigmask;
    sa_terminate.sa_flags = 0;
    sigaction(SIGHUP,  &sa_terminate, NULL);
    sigaction(SIGQUIT, &sa_terminate, NULL);
    sigaction(SIGINT,  &sa_terminate, NULL);
    sigaction(SIGTERM, &sa_terminate, NULL);


    if (pipe(_cnf->connect_fd) == -1)
    {
        ui_log_errno(LOG_ERR, "Creation of connection pipe failed!");
        return -1;
    }


    if (pipe(_cnf->cl_change) == -1)
    {
        ui_log_errno(LOG_ERR, "Creation of change pipe failed!");
        return -1;
    }


    if (pipe(_cnf->user_input) == -1)
    {
        ui_log_errno(LOG_ERR, "Creation of userinput pipe faild!");
        return -1;
    }


    if (pthread_mutex_init(&_cnf->cl.cl_mx, NULL))
    {
        ui_log_errno(LOG_ERR, "Initialization of mutex failed!");
        return -1;
    }


    if (pthread_create
        (&_cnf->conn_th, NULL, (void* (*)(void*)) th_new_conn, _cnf) == -1)
    {
        ui_log_errno(LOG_ERR, "Creation of connection thread failed!");
        return -1;
    }


    if (pthread_create
        (&_cnf->select_th, NULL, (void* (*)(void*)) th_main_loop, _cnf) == -1)
    {
        ui_log_errno(LOG_ERR, "Creation of selection thread failed!");
        return -1;
    }


    pthread_sigmask(SIG_UNBLOCK, &sigmask, NULL);
    return 0;
}
