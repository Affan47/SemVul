waitForServer(struct display *d)
{
    volatile int i;


    i = 0;
    do {
        (void)Signal(SIGALRM, abortOpen);
        (void)alarm((unsigned)d->openTimeout);
        if (!Setjmp(openAbort)) {
            debug("before XOpenDisplay(%s)\n", d->name);
            errno = 0;
            (void)XSetIOErrorHandler(openErrorHandler);
            dpy = XOpenDisplay(d->name);
#ifdef STREAMSCONN
            {


                Display *bogusDpy = XOpenDisplay(d->name);
                debug("bogus XOpenDisplay %s\n",
                      bogusDpy ? "succeeded" : "failed");
                if (bogusDpy)
                    XCloseDisplay(bogusDpy);
            }
#endif
            (void)alarm((unsigned)0);
            (void)Signal(SIGALRM, SIG_DFL);
            (void)XSetIOErrorHandler((int (*)(Display *)) 0);
            debug("after XOpenDisplay(%s)\n", d->name);
            if (dpy) {
#ifdef XDMCP
                if ((d->displayType & d_location) == dForeign)
                    getRemoteAddress(d, ConnectionNumber(dpy));
#endif
                registerCloseOnFork(ConnectionNumber(dpy));
                return;
            }
            debug("OpenDisplay(%s) attempt %d failed: %m\n", d->name, i + 1);
            sleep((unsigned)d->openDelay);
        } else {
            logError("Hung in XOpenDisplay(%s), aborting\n", d->name);
            (void)Signal(SIGALRM, SIG_DFL);
            break;
        }
    } while (++i < d->openRepeat);
    logError("Cannot connect to %s, giving up\n", d->name);
    exit(EX_OPENFAILED_DPY);
}
