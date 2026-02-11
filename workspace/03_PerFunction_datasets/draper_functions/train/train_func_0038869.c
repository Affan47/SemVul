resolve_hostname_or_ip_addr(
    const char* hostname, sockaddr_storage &ip_addr
) {
#ifdef _WIN32
    int x = inet_addr(hostname);
    if (x != -1) {
        sockaddr_in* sin = (sockaddr_in*)&ip_addr;
        sin->sin_family = AF_INET;
        sin->sin_addr.s_addr = x;
        return 0;
    }
#else
    int retval;


    sockaddr_in* sin = (sockaddr_in*)&ip_addr;
    retval = inet_pton(AF_INET, hostname, &sin->sin_addr);
    if (retval > 0) {
        ip_addr.ss_family = AF_INET;
        return 0;
    }
    sockaddr_in6* sin6 = (sockaddr_in6*)&ip_addr;
    retval = inet_pton(AF_INET6, hostname, &sin6->sin6_addr);
    if (retval > 0) {
        ip_addr.ss_family = AF_INET6;
        return 0;
    }
#endif


    return resolve_hostname(hostname, ip_addr);
}
