same_ip_addr(sockaddr_storage& s1, sockaddr_storage& s2) {
#ifdef _WIN32
    return (s1.sin_addr.s_addr == s2.sin_addr.s_addr);
#else
    if (s1.ss_family != s2.ss_family) return false;
    switch (s1.ss_family) {
        case AF_INET: {
            sockaddr_in* sin1 = (sockaddr_in*)&s1;
            sockaddr_in* sin2 = (sockaddr_in*)&s2;
            return (memcmp((void*)(&sin1->sin_addr), (void*)(&sin2->sin_addr), sizeof(in_addr)) == 0);
            break;
        }
        case AF_INET6: {
            sockaddr_in6* sin1 = (sockaddr_in6*)&s1;
            sockaddr_in6* sin2 = (sockaddr_in6*)&s2;
            return (memcmp((void*)(&sin1->sin6_addr), (void*)(&sin2->sin6_addr), sizeof(in6_addr)) == 0);
            break;
        }
    }
    return false;
#endif
}
