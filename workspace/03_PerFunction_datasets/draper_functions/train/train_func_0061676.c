add_range(char *start, char *end)
{
    struct addrinfo addr_hints;
    struct addrinfo *addr_res;
    unsigned long start_long;
    unsigned long end_long;
    int ret;


    memset(&addr_hints, 0, sizeof(struct addrinfo));
    addr_hints.ai_family = AF_UNSPEC;
    addr_hints.ai_flags = AI_NUMERICHOST;
    ret = getaddrinfo(start, NULL, &addr_hints, &addr_res);
    if(ret) {
        fprintf(stderr, "Error: can't parse address %s: %s\n", start, gai_strerror(ret));
        exit(2);
    }
    if(addr_res->ai_family != AF_INET) {
        fprintf(stderr, "Error: -g works only with IPv4 addresses\n");
        exit(2);
    }
    start_long = ntohl(((struct sockaddr_in *) addr_res->ai_addr)->sin_addr.s_addr);


    memset(&addr_hints, 0, sizeof(struct addrinfo));
    addr_hints.ai_family = AF_UNSPEC;
    addr_hints.ai_flags = AI_NUMERICHOST;
    ret = getaddrinfo(end, NULL, &addr_hints, &addr_res);
    if(ret) {
        fprintf(stderr, "Error: can't parse address %s: %s\n", end, gai_strerror(ret));
        exit(2);
    }
    if(addr_res->ai_family != AF_INET) {
        fprintf(stderr, "Error: -g works only with IPv4 addresses\n");
        exit(2);
    }
    end_long = ntohl(((struct sockaddr_in *) addr_res->ai_addr)->sin_addr.s_addr);


    while(start_long <= end_long) {
        struct in_addr in_addr_tmp;
        char buffer[20];
        in_addr_tmp.s_addr = htonl(start_long);
        inet_ntop(AF_INET, &in_addr_tmp, buffer, sizeof(buffer));
        add_name(buffer);
        start_long++;
    }
}
