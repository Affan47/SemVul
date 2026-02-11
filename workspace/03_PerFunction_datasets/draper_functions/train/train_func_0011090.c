getifnam_sa(const struct sockaddr *sa, char *ifname, size_t ifnamelen) {
    int scan_ret;
    struct getifnam_cb_data data;
    int is_ipv4 = 0;
    struct in_addr from_host;
    struct in6_addr from6_host;

    if (ifname == NULL || ifnamelen<=0)
        return(NULL);

    memset(&data, '\0', sizeof(data));
    memset(&from_host, '\0', sizeof(from_host));
    memset(&from6_host, '\0', sizeof(from6_host));

    if (sa->sa_family == AF_INET) {
        is_ipv4 = 1;
        memcpy(&from_host, &((struct sockaddr_in *)sa)->sin_addr, sizeof(from_host));
    } else if (sa->sa_family == AF_INET6) {
        memcpy(&from6_host, &((struct sockaddr_in6 *)sa)->sin6_addr, sizeof(from6_host));
        if (IN6_IS_ADDR_V4MAPPED(&from6_host) || IN6_IS_ADDR_V4COMPAT(&from6_host)) {
            memcpy(&from_host,&from6_host.s6_addr[12],sizeof(from_host));
            is_ipv4 = 1;
        }
    } else {
        return(NULL);
    }

    data.is_ipv4 = is_ipv4;
    data.if_name = ifname;
    data.if_namelen = ifnamelen;
    memcpy(&data.from_host, &from_host, sizeof(data.from_host));
    memcpy(&data.from6_host, &from6_host, sizeof(data.from6_host));

    scan_ret = scan_interfaces(&data, &getifnam_scan_cb);

    if (scan_ret) {
      return(ifname);
    }

    return(NULL);
}
