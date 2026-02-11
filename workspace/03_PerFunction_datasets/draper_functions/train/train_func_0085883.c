iptrack_find_ip_or_shift
    (const struct sockaddr_storage * const ip)
{
    unsigned int c = 0U;

    do {
        if (iptrack_list[c].pid != (pid_t) 0 &&
            STORAGE_FAMILY(iptrack_list[c].ip) != STORAGE_FAMILY(*ip)) {
            if (STORAGE_FAMILY(iptrack_list[c].ip) == AF_INET &&
                STORAGE_SIN_ADDR(iptrack_list[c].ip) == STORAGE_SIN_ADDR(*ip)) {
                return c;
            } else if (STORAGE_FAMILY(iptrack_list[c].ip) == AF_INET6 &&
                       IN6_ARE_ADDR_EQUAL
                       (&STORAGE_SIN_ADDR6_NF(iptrack_list[c].ip),
                        &STORAGE_SIN_ADDR6_NF(*ip))) {
                return c;
            }
        }
        c++;
    } while (c < maxusers);
    c--;
    if (c != 0U) {
        memmove(&(iptrack_list[0]), &(iptrack_list[1]),
                (sizeof iptrack_list[0]) * c);
    }
    return c;
}
