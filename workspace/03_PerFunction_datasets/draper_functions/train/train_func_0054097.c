ttflui() {
#ifdef BSD
    long n = 1;
#endif
    int x;
    tincnt = 0;
    tlast = 0;
    tinptr = tinbuf;
    errno = 0;
#ifdef POSIX
    x = tcflush(0,TCIFLUSH);
#else
#ifdef SYSV
    x = ioctl(0,TCFLSH,0);
#else
#ifdef BSD
    x = ioctl(0,TIOCFLUSH,&n);
#endif
#endif
#endif
    if (debug) fprintf(db,"ttflui = %d, errno = %d\n",x,errno);
    return(x);
}
