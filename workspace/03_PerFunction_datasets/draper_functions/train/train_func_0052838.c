make_hints(struct addrinfo *hints, int proto)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_UNSPEC;
    switch(proto) {
    case KRB5_KRBHST_UDP :
	hints->ai_socktype = SOCK_DGRAM;
	break;
    case KRB5_KRBHST_HTTP :
    case KRB5_KRBHST_TCP :
	hints->ai_socktype = SOCK_STREAM;
	break;
    }
}
