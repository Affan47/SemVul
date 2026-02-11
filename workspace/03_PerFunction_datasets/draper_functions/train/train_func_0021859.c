s_ntop(char *text, SOCKADDR_UNION *addr) {
    char host[IPLEN-6], port[6];

    if(getnameinfo(&addr->sa, addr_len(*addr),
            host, IPLEN-6, port, 6, NI_NUMERICHOST|NI_NUMERICSERV)) {
        sockerror("getnameinfo");
        strcpy(text, "unresolvable IP");
        return text;
    }
    strcpy(text, host);
    strcat(text, ":");
    strcat(text, port);
    return text;
}
