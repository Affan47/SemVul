FallbackDefineSelf(fd)
#else
DefineSelf(fd)
#endif
int fd;
{
#if !defined(TCPCONN) && !defined(UNIXCONN)
    return -1;
#else
    int len;
    caddr_t addr;
    int family;
    HOST *host;

    struct utsname name;
    struct hostent *hp;

    union {
        struct sockaddr sa;
        struct sockaddr_in in;
    } saddr;

    struct sockaddr_in *inetaddr;


    uname(&name);
    hp = gethostbyname(name.nodename);
    if (hp != NULL) {
        saddr.sa.sa_family = hp->h_addrtype;
        inetaddr = (struct sockaddr_in *) (&(saddr.sa));
        acopy(hp->h_addr, &(inetaddr->sin_addr), hp->h_length);
        len = sizeof(saddr.sa);
        family = ConvertAddr(&(saddr.sa), &len, &addr);
        if (family != -1 && family != FamilyLocal) {
            for (host = selfhosts;
                 host && !addrEqual(family, addr, len, host);
                 host = host->next);
            if (!host) {

                MakeHost(host, len)
                        if (host) {
                    host->family = family;
                    host->len = len;
                    acopy(addr, host->addr, len);
                    host->next = selfhosts;
                    selfhosts = host;
                }
            }
        }
    }
#endif
}
