netsnmp_swinst_container_load( netsnmp_container *user_container, int flags )
{
    netsnmp_container *container = user_container;
    int arch_rc;

    DEBUGMSGTL(("swinst:container", "load\n"));


    if (NULL == container) {
        container = netsnmp_container_find("swinst:table_container");
        if (NULL == container)
            return NULL;
    }
    if (NULL == container->container_name)
        container->container_name = strdup("swinst container");


    arch_rc = netsnmp_swinst_arch_load( container, flags );
    if (arch_rc && (flags & NETSNMP_SWINST_ALL_OR_NONE)) {


        netsnmp_swinst_container_free_items(container);
        if (container != user_container) {
            netsnmp_swinst_container_free(container, flags);
        }
    }

    return container;
}
