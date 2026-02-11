NsInitThreads(void)
{
    char *env;
    int err;

    err = pthread_key_create(&key, FreeThread);
    if (err != 0) {
	NsThreadFatal("NsPthreadsInit", "pthread_key_create", err);
    }
    stackdown = StackDown(&env);
    pagesize = getpagesize();
    env = getenv("NS_THREAD_GUARDSIZE");
    if (env == NULL
	    || Tcl_GetInt(NULL, env, &guardsize) != TCL_OK
	    || guardsize < 2) {
	guardsize = 2 * pagesize;
    }
    guardsize = PageRound(guardsize);
    markpages = getenv("NS_THREAD_MARKPAGES") ? 1 : 0;
    dumpdir = getenv("NS_THREAD_DUMPDIR");
    env = getenv("NS_THREAD_LOGFILE");
    if (env != NULL) {
	if (strcmp(env, "-") == 0) {
	    logfp = stderr;
	} else {
	    logfp = fopen(env, "a");
	}
    }
    Ns_MutexSetName(&uidlock, "ns:uidlock");
}
