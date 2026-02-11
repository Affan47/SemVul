globus_libc_getaddrinfo(
    const char *                        node,
    const char *                        service,
    const globus_addrinfo_t *           hints,
    globus_addrinfo_t **                res)
{
    int                                 rc;
    globus_result_t                     result;
    const char *                        port_str = service;

#ifdef TARGET_ARCH_AIX5
    if(port_str && port_str[0] == '0' && port_str[1] == '\0')
    {


        port_str = "56789";
    }
#endif

    result = GLOBUS_SUCCESS;

    rc = getaddrinfo(node, port_str, hints, res);
    if(rc != 0)
    {
#   ifdef EAI_SYSTEM
        if(rc == EAI_SYSTEM)
        {
            result = globus_error_put(
                globus_error_wrap_errno_error(
                    GLOBUS_COMMON_MODULE,
                    errno,
                    rc + GLOBUS_EAI_ERROR_OFFSET,
                    __FILE__,
                    "globus_libc_getaddrinfo",
                    __LINE__,
                    "%s",
                    gai_strerror(rc)));
        }
        else
#   endif
        {
            result = globus_error_put(
                globus_error_construct_error(
                    GLOBUS_COMMON_MODULE,
                    GLOBUS_NULL,
                    rc + GLOBUS_EAI_ERROR_OFFSET,
                    __FILE__,
                    "globus_libc_getaddrinfo",
                    __LINE__,
                    "%s",
                    gai_strerror(rc)));
        }
        goto error;
    }

#ifdef TARGET_ARCH_AIX5
    {
        globus_addrinfo_t *             addrinfo;


        for(addrinfo = *res;
            addrinfo;
            addrinfo = addrinfo->ai_next)
        {
            if(GlobusLibcProtocolFamilyIsIP(addrinfo->ai_family))
            {
                GlobusLibcSockaddrSetFamily(
                    *addrinfo->ai_addr, addrinfo->ai_family);
                GlobusLibcSockaddrSetLen(
                   *addrinfo->ai_addr, addrinfo->ai_addrlen);
                if(port_str != service)
                {
                    GlobusLibcSockaddrSetPort(*addrinfo->ai_addr, 0);
                }
            }
        }
    }
#endif

    return result;

error:
    return result;
}
