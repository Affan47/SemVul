GetHost(Ns_DString *dsPtr, char *addr)
{
#if defined(HAVE_GETNAMEINFO)
    char buf[NI_MAXHOST];
    int err;
#elif defined(HAVE_GETHOSTBYADDR_R)
    struct hostent he, *hp;
    char buf[2048];
    int err;
#else
    struct hostent *hp;
    static Ns_Cs cs;
#endif
    struct sockaddr_in sa;
    char *host;

    host = NULL;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(addr);
    if (sa.sin_addr.s_addr == INADDR_NONE) {
	return NS_FALSE;
    }
#if defined(HAVE_GETNAMEINFO)
    err = getnameinfo((const struct sockaddr *) &sa,
                      sizeof(struct sockaddr_in), buf, sizeof(buf),
                      NULL, 0, NI_NAMEREQD);
    if (err != 0) {
        Ns_Log(Error, "dns: getnameinfo failed: %s", gai_strerror(err));
    } else {
	host = buf;
    }
#elif defined(HAVE_GETHOSTBYADDR_R)
    hp = gethostbyaddr_r((char *) &sa.sin_addr, sizeof(struct in_addr),
            AF_INET, &he, buf, sizeof(buf), &err);
    if (hp == NULL) {
        DnsLogError("gethostbyaddr_r", err);
    } else {
	host = he.h_name;
    }
#else


    Ns_CsEnter(&cs);
    hp = gethostbyaddr((char *) &sa.sin_addr, sizeof(struct in_addr), AF_INET);
    if (hp == NULL) {
	DnsLogError("gethostbyaddr", h_errno);
    } else {
	host = hp->h_name;
    }
    Ns_CsLeave(&cs);
#endif
    if (host == NULL) {
	return NS_FALSE;
    }
    Ns_DStringAppend(dsPtr, host);
    return NS_TRUE;
}
