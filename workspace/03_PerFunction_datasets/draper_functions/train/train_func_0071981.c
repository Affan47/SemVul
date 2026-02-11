udp_sendto(int s, Octstr *datagram, Octstr *addr)
{
    struct sockaddr_in sa;

    gw_assert(octstr_len(addr) == sizeof(sa));
    memcpy(&sa, octstr_get_cstr(addr), sizeof(sa));
    if (sendto(s, octstr_get_cstr(datagram), octstr_len(datagram), 0,
               (struct sockaddr *) &sa, (int) sizeof(sa)) == -1) {
        error(errno, "Couldn't send UDP packet");
        return -1;
    }
    return 0;
}
