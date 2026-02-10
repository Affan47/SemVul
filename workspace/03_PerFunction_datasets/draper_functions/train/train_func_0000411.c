swrun_count_processes( void )
{
    netsnmp_cache_check_and_reload(swrun_cache);
    return ( swrun_container ? CONTAINER_SIZE(swrun_container) : 0 );
}
