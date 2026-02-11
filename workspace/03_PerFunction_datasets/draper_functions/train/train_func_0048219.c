sp_init(const char* name)
{
    int r;

    ASSERT(name);

    memset(&g_state, 0, sizeof(g_state));

    sp_message(NULL, LOG_DEBUG, "%s (%s)", name, VERSION);


    g_state.debug_level = -1;
    g_state.max_threads = DEFAULT_MAXTHREADS;
    g_state.timeout.tv_sec = DEFAULT_TIMEOUT;
    g_state.keepalives = DEFAULT_KEEPALIVES;
    g_state.directory = _PATH_TMP;
    g_state.name = name;


    r = sp_parse_option(CFG_LISTENADDR, DEFAULT_SOCKET);
    ASSERT(r == 1);


    if(pthread_mutexattr_init(&g_mtxattr) != 0 ||
#ifdef HAVE_ERR_MUTEX
       pthread_mutexattr_settype(&g_mtxattr, MUTEX_TYPE) ||
#endif
       pthread_mutex_init(&g_mutex, &g_mtxattr) != 0)
        errx(1, "threading problem. can't create mutex or condition var");
}
