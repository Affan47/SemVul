main_init(void)
{
    if (dns_cache_init(Options.opt_cache_size, Options.opt_threads + DNS_SOCK_THREADS + 1) < 0)
        return -1;

    if (dns_sock_init() < 0)
        return -1;
    if (dns_control_init() < 0)
        return -1;
    if (dns_session_init() < 0)
        return -1;

    return 0;
}
