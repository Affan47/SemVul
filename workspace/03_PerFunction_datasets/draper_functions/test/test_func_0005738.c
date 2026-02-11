netsnmp_get_watcher_handler(void)
{
    netsnmp_mib_handler *ret = NULL;

    ret = netsnmp_create_handler("watcher",
                                 netsnmp_watcher_helper_handler);
    if (ret) {
        ret->flags |= MIB_HANDLER_AUTO_NEXT;
    }
    return ret;
}
