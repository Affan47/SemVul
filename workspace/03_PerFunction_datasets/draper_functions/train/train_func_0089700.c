parse_address(struct sockaddr_storage* saddr, const char* address, int port) {
    union {
        struct sockaddr_storage *storage;
        struct sockaddr_in *sin;
        struct sockaddr_in6 *sin6;
        struct sockaddr_un *sun;
    } addr;
    addr.storage = saddr;

    memset(addr.storage, 0, sizeof(struct sockaddr_storage));
    if (address == NULL) {
        addr.sin6->sin6_family = AF_INET6;
        addr.sin6->sin6_port = htons(port);
        return sizeof(struct sockaddr_in6);
    }

    if (inet_pton(AF_INET, address, &addr.sin->sin_addr) == 1) {
        addr.sin->sin_family = AF_INET;
        addr.sin->sin_port = htons(port);
        return sizeof(struct sockaddr_in);
    }


    memset(addr.storage, 0, sizeof(struct sockaddr_storage));
    if (inet_pton(AF_INET6, address, &addr.sin6->sin6_addr) == 1) {
        addr.sin6->sin6_family = AF_INET6;
        addr.sin6->sin6_port = htons(port);
        return sizeof(struct sockaddr_in6);
    }

    memset(addr.storage, 0, sizeof(struct sockaddr_storage));
    if (strncmp("unix:", address, 5) == 0) {
        addr.sun->sun_family = AF_UNIX;
        strncpy(addr.sun->sun_path, address + 5, UNIX_PATH_MAX);
        return offsetof(struct sockaddr_un, sun_path) + strlen(addr.sun->sun_path);
    }

    return 0;
}
