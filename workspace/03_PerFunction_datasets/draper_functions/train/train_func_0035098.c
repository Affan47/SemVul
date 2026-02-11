hostport2addrlist(SOCKADDR_LIST *addr_list,
        char *hostname, char *portname) {
    struct addrinfo hints, *res=NULL, *cur;
    int err;

    addr_list->cur=0;

    memset(&hints, 0, sizeof hints);
#if defined(USE_IPv6) || defined(USE_WIN32)
    hints.ai_family=PF_UNSPEC;
#else
    hints.ai_family=PF_INET;
#endif
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_protocol=IPPROTO_TCP;
    do {
        err=getaddrinfo(hostname, portname, &hints, &res);
        if(err && res)
            freeaddrinfo(res);
        if(err==EAI_AGAIN) {
            s_log(LOG_DEBUG, "getaddrinfo: EAI_AGAIN received: retrying");
            sleep(1);
        }
    } while(err==EAI_AGAIN);
    switch(err) {
    case 0:
        break;
    case EAI_SERVICE:
        s_log(LOG_ERR, "Unknown TCP service '%s'", portname);
        return 0;
    default:
        s_log(LOG_ERR, "Error resolving '%s': %s",
            hostname, s_gai_strerror(err));
        return 0;
    }


    for(cur=res; cur && addr_list->num<MAX_HOSTS;
            cur=cur->ai_next, addr_list->num++) {
        if(cur->ai_addrlen>sizeof(SOCKADDR_UNION)) {
            s_log(LOG_ERR, "INTERNAL ERROR: ai_addrlen value too big");
            freeaddrinfo(res);
            return 0;
        }
        memcpy(&addr_list->addr[addr_list->num],
            cur->ai_addr, cur->ai_addrlen);
    }
    freeaddrinfo(res);
    return addr_list->num;
}
