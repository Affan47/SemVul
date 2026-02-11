switchToTTY(void)
#else
switchToTTY(struct display *d)
#endif
{
    struct utmps *utp;
#ifdef HAVE_VTS
    int vt;
#endif

    if (!(utp = Malloc(sizeof(*utp)))) {
#ifdef HAVE_VTS
        wakeDisplays();
#else
        d->status = notRunning;
#endif
        return;
    }
#ifndef HAVE_VTS
    d->status = textMode;
    utp->d = d;
    utp->next = utmpList;
#endif
    utp->time = now;
    utp->hadSess = False;
    utmpList = utp;
    checkUtmp();

#ifdef HAVE_VTS
    if ((vt = TTYtoVT(*consoleTTYs)))
        activateVT(vt);
#endif
}
