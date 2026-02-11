dns_util_sainit(struct sockaddr *sa, int af)
{
    struct sockaddr_in *sin;
    struct sockaddr_in6 *sin6;


    switch (af) {
    case AF_INET:
        sin = (struct sockaddr_in *) sa;
        memset(sin, 0, sizeof(*sin));
        sin->sin_family = AF_INET;
        break;

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) sa;
        memset(sin6, 0, sizeof(*sin6));
        sin6->sin6_family = AF_INET6;
        break;
    }
}
