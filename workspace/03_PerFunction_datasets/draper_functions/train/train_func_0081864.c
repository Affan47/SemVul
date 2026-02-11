get_os_statistics(struct os_statistics *stats) {

    int res = 1;
    _OSBASE_TRACE(3,("get_os_statistics() called"));
#ifdef CHECK_FCT_PARAMS
    if (stats == NULL) {
        return res;
        _OSBASE_TRACE(1,("get_os_statistics(): stats parameter is NULL"));
    }
#endif

    stats->user_time = 0;
    stats->system_time = 0;
    stats->wait_time = 0;
    stats->idle_time = 0;
    stats->run_queue_length = 0;
    stats->block_queue_length = 0;
    stats->pages_in = 0;
    stats->pages_out = 0;

    if (is_kernel26()) {
        res = get_cpu_queue_data_26(stats);
        res = res && get_pages_26(stats);
    } else {
        res = get_cpu_page_data_24(stats);
        res = res && get_queue_info_24(stats);
        res = res && get_wait_time_24(stats);
    }
    _OSBASE_TRACE(4,("get_os_statistics() res: %d",res));
    _OSBASE_TRACE(3,("get_os_statistics() exited"));

    return (res == 0);
}
