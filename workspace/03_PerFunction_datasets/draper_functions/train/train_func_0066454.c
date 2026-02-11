MakeUNIXSocketConnection (
    char *phostname,
    int *iserverp,
    AuBool xname,
    int retries,
    int *familyp,
    int *saddrlenp,
    char **saddrp
    )
{
    struct sockaddr_un unaddr;
    struct sockaddr *addr;
    int addrlen;
    int fd;
#ifdef hpux
    struct sockaddr_un ounaddr;
    struct sockaddr *oaddr;
    int oaddrlen;
#endif

    unaddr.sun_family = AF_UNIX;
    sprintf (unaddr.sun_path, "%s%d", AU_DEFAULT_UNIX_PATH, *iserverp);
#ifdef BSD44SOCKETS
    unaddr.sun_len = strlen(unaddr.sun_path);
#endif

    addr = (struct sockaddr *) &unaddr;
#ifdef BSD44SOCKETS
    addrlen = SUN_LEN(&unaddr);
#else
    addrlen = strlen(unaddr.sun_path) + sizeof(unaddr.sun_family);
#endif

#ifdef DEBUG
    fprintf(stderr, "MakeUNIXSocketConnection: starting, *iserverp = %d\n",
	    *iserverp);
#endif


    do {
	if ((fd = socket ((int) addr->sa_family, SOCK_STREAM, 0)) < 0) {
#ifdef DEBUG
          fprintf(stderr,
                  "MakeUNIXSocketConnection: socket errno = %d\n", errno);
#endif

	    return -1;
	}

	if (connect (fd, addr, addrlen) < 0) {
#ifdef DEBUG
          fprintf(stderr,
                  "MakeUNIXSocketConnection: connect errno = %d\n", errno);
#endif
	    int olderrno = errno;
	    (void) close (fd);
#ifdef hpux
	    if (olderrno == ENOENT) {
		fd = socket ((int) oaddr->sa_family, SOCK_STREAM, 0);
		if (fd >= 0) {
		    if (connect (fd, oaddr, oaddrlen) >= 0)
			break;
		    olderrno = errno;
		    (void) close (fd);
		}
	    }
#endif
	    if (olderrno != ENOENT || retries <= 0) {
		errno = olderrno;
#ifdef DEBUG
                fprintf(stderr,
                        "MakeUNIXSocketConnection: errno = %d\n", errno);
#endif

		return -1;
	    }
	    sleep (1);
	} else {
	    break;
	}
    } while (retries-- > 0);


    return fd;
}
