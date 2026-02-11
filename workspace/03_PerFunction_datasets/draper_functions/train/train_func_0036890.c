netsnmp_access_defaultrouter_container_load(netsnmp_container* container,
                                            u_int load_flags)
{
    int rc;
     u_int container_flags = 0;

    DEBUGMSGTL(("access:defaultrouter:container", "load\n"));

    if (NULL == container) {
        if (load_flags & NETSNMP_ACCESS_DEFAULTROUTER_LOAD_ADDL_IDX_BY_ADDR) {
            container_flags |=
                NETSNMP_ACCESS_DEFAULTROUTER_INIT_ADDL_IDX_BY_ADDR;
        }
        container =
            netsnmp_access_defaultrouter_container_init(container_flags);
    }

    if (NULL == container) {
        snmp_log(LOG_ERR, "no container specified/found for access_defaultrouter\n");
        return NULL;
    }

    rc =  netsnmp_arch_defaultrouter_container_load(container, load_flags);
    if (0 != rc) {
        netsnmp_access_defaultrouter_container_free(container,
                                    NETSNMP_ACCESS_DEFAULTROUTER_FREE_NOFLAGS);
        container = NULL;
    }

    return container;
}
