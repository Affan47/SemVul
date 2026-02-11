globus_libc_gethostaddr_by_family(
    globus_sockaddr_t *                 addr,
    int                                 family)
{
    int                                 rc;
    char                                hostname[MAXHOSTNAMELEN];
    globus_addrinfo_t                   hints;
    globus_addrinfo_t *                 save_addrinfo;
    globus_addrinfo_t *                 addrinfo;
    globus_result_t                     result;

    rc = globus_libc_gethostname(hostname, sizeof(hostname));
    if(rc < 0)
    {
        return rc;
    }

    memset(&hints, 0, sizeof(globus_addrinfo_t));
    hints.ai_flags = 0;
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    result = globus_libc_getaddrinfo(
        hostname, GLOBUS_NULL, &hints, &save_addrinfo);
    if(result != GLOBUS_SUCCESS)
    {
        return -1;
    }

    for(addrinfo = save_addrinfo; addrinfo; addrinfo = addrinfo->ai_next)
    {
        if(GlobusLibcProtocolFamilyIsIP(addrinfo->ai_family))
        {
            memcpy(addr, addrinfo->ai_addr, addrinfo->ai_addrlen);

            break;
        }
    }

    globus_libc_freeaddrinfo(save_addrinfo);

    return 0;
}
