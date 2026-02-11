local_resolve (const char *host, struct sockaddr_in *addr)
{
    struct hostent *ent;
    if ( strspn(host, dotdigits) == strlen(host) ) {

        addr->sin_family = AF_INET;
        addr->sin_addr.s_addr = inet_addr(host);
    } else {
        debug("resolving host by name: %s\n", host);
        ent = gethostbyname (host);
        if ( ent ) {
            memcpy (&addr->sin_addr, ent->h_addr, ent->h_length);
            addr->sin_family = ent->h_addrtype;
            debug("resolved: %s (%s)\n",
                  host, inet_ntoa(addr->sin_addr));
        } else {
            debug("failed to resolve locally.\n");
            return -1;
        }
    }
    return 0;
}
