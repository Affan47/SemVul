get_host(char *const name, struct addrinfo *res, int ai_family)
{
    struct addrinfo *chain, *ap;
    struct addrinfo hints;
    int             ret_val;

#ifdef  HAVE_INET_NTOP
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = ai_family;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    if((ret_val = getaddrinfo(name, NULL, &hints, &chain)) == 0) {
#ifdef _AIX
        ap = chain;
#else
        for(ap = chain; ap != NULL; ap = ap->ai_next)
            if(ap->ai_socktype == SOCK_STREAM)
                break;
#endif
        if(ap == NULL) {
            freeaddrinfo(chain);
            return EAI_NONAME;
        }
        *res = *ap;
        if((res->ai_addr = (struct sockaddr *)malloc(ap->ai_addrlen)) == NULL) {
            freeaddrinfo(chain);
            return EAI_MEMORY;
        }
        memcpy(res->ai_addr, ap->ai_addr, ap->ai_addrlen);
        freeaddrinfo(chain);
    }
#else
#error  "Pound requires getaddrinfo()"
#endif
    return ret_val;
}
