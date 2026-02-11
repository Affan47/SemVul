init_cpu( void ) {
    oid nsCPU[] = { 1, 3, 6, 1, 4, 1, 8072, 1, 33 };


    if ( _cpuAutoUpdate ) {

        _cpuHistoryLen = 60/_cpuAutoUpdate;
        snmp_alarm_register( _cpuAutoUpdate, SA_REPEAT, _cpu_update_stats,
                             NULL );
        if ( _cpu_head )
            _cpu_update_stats( 0, NULL );
    } else
        _cpu_cache = netsnmp_cache_create( 5, netsnmp_cpu_arch_load, NULL,
                                              nsCPU, OID_LENGTH(nsCPU));
}
