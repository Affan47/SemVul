start_server(void)
{
    int             rval, nbsillymsg;
    pthread_attr_t  impthread_attr;

#ifndef WIN32_NOTCYGWIN


    fclose(stdin);
    fclose(stdout);


#endif


    dbgprintf("Setting up deadly signals handler\n");
    im_signal(SIGABRT, abortHandler);
    im_signal(SIGBUS, abortHandler);
    im_signal(SIGSEGV, abortHandler);
    im_signal(SIGKILL, abortHandler);
    im_signal(SIGHUP, abortHandler);
    im_signal(SIGQUIT, abortHandler);
    im_signal(SIGTERM, abortHandler);
    im_signal(SIGINT, abortHandler);
    if (im_setjmp(abortenv, 1) == 0) {
	if ((rval = pthread_attr_init(&impthread_attr)) == 0)
#if HAVE_DECTHREADS
	    rval = pthread_create(&serverthread,
				  impthread_attr,
				  (mt) init_server, 0);
#else
	    rval = pthread_create(&serverthread,
				  &impthread_attr,
				  (mt) init_server, 0);
#endif
	    serverIsRunning = true;
	if (rval) {
	    errprintf("Server could not be started\n");
	} else
	    dbgprintf("Server started\n");
    } else {
        for (nbsillymsg = 0 ; silly_messages[nbsillymsg] != NULL; ++nbsillymsg)
            ;

        int index = (int)((double)random()/INT_MAX * nbsillymsg);
        dbgprintf("Printing silly message %d\n", index);
	fprintf(stderr, "\n*** Aaargh, deadly signal caught: imview %s\n", silly_messages[index]);
	serverIsRunning = false;
	imview_exit(101);
    }

    return;
}
