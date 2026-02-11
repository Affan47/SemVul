get_local_network_info() {
    strcpy(ip_addr, "");

#ifdef ANDROID
    if (strlen(domain_name) && strcmp(domain_name, "localhost")) return 0;
    char buf[256];
    make_random_string("", buf);
    buf[8] = 0;
    sprintf(domain_name, "android_%s", buf);
    return 0;
#endif

    struct sockaddr_storage s;

    strcpy(domain_name, "");


    if (gethostname(domain_name, 256)) {
        return ERR_GETHOSTBYNAME;
    }
    int retval = resolve_hostname(domain_name, s);
    if (retval) return retval;
#ifdef _WIN32
    sockaddr_in* sin = (sockaddr_in*)&s;
    strlcpy(ip_addr, inet_ntoa(sin->sin_addr), sizeof(ip_addr));
#else
    if (s.ss_family == AF_INET) {
        sockaddr_in* sin = (sockaddr_in*)&s;
        inet_ntop(AF_INET, (void*)(&sin->sin_addr), ip_addr, 256);
    } else {
        sockaddr_in6* sin = (sockaddr_in6*)&s;
        inet_ntop(AF_INET6, (void*)(&sin->sin6_addr), ip_addr, 256);
    }
#endif
    return 0;
}
