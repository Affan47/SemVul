iptrack_get(const struct sockaddr_storage * const ip)
{
    unsigned int c = 0U;
    unsigned int nb = 0U;

    if (iptrack_list == NULL) {
        return 0U;
    }
    do {
        if (iptrack_list[c].pid != (pid_t) 0 &&
            STORAGE_FAMILY(iptrack_list[c].ip) == STORAGE_FAMILY(*ip)) {
            if (STORAGE_FAMILY(iptrack_list[c].ip) == AF_INET &&
                STORAGE_SIN_ADDR(iptrack_list[c].ip) == STORAGE_SIN_ADDR(*ip)) {
                nb++;
            } else if (STORAGE_FAMILY(iptrack_list[c].ip) == AF_INET6 &&
                       IN6_ARE_ADDR_EQUAL
                       (&STORAGE_SIN_ADDR6_NF(iptrack_list[c].ip),
                        &STORAGE_SIN_ADDR6_NF(*ip))) {
                nb++;
            }
        }
        c++;
    } while (c < maxusers);

    return nb;
}
