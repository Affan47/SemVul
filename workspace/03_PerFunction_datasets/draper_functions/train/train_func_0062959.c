netsnmp_access_interface_entry_get_by_name(netsnmp_container *container,
                                const char *name)
{
    netsnmp_interface_entry tmp;

    DEBUGMSGTL(("access:interface:entry", "by_name\n"));
    netsnmp_assert(1 == _access_interface_init);

    if (NULL == container) {
        snmp_log(LOG_ERR,
                 "invalid container for netsnmp_access_interface_entry_get_by_name\n");
        return NULL;
    }

    if (NULL == container->next) {
        snmp_log(LOG_ERR,
                 "secondary index missing for netsnmp_access_interface_entry_get_by_name\n");
        return NULL;
    }

    tmp.name = NETSNMP_REMOVE_CONST(char *, name);
    return (netsnmp_interface_entry*)CONTAINER_FIND(container->next, &tmp);
}
