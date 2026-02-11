ipIfStatsTable_container_load(netsnmp_container * container)
{
    netsnmp_container *stats;

    DEBUGMSGTL(("verbose:ipIfStatsTable:ipIfStatsTable_container_load",
                "called\n"));

    netsnmp_assert(NULL != container);

    stats = netsnmp_access_systemstats_container_load(NULL, NETSNMP_ACCESS_SYSTEMSTATS_LOAD_IFTABLE);
    if (NULL == stats)
        return MFD_RESOURCE_UNAVAILABLE;


    CONTAINER_FOR_EACH(container, (netsnmp_container_obj_func *)
                       _check_for_updates, stats);


    CONTAINER_FOR_EACH(stats, (netsnmp_container_obj_func *)
                       _add_new, container);


    netsnmp_access_systemstats_container_free(stats,
                                          NETSNMP_ACCESS_SYSTEMSTATS_FREE_DONT_CLEAR);

    DEBUGMSGT(("verbose:ipIfStatsTable:ipIfStatsTable_container_load",
               "%lu records\n", (unsigned long)CONTAINER_SIZE(container)));

    return MFD_SUCCESS;
}
