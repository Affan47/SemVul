comm_init(void)
{
#if DELAY_POOLS
    int i;
#endif
    fd_init();


    RESERVED_FD = XMIN(100, Squid_MaxFD / 4);
    CBDATA_INIT_TYPE(ConnectStateData);
    comm_write_pool = memPoolCreate("CommWriteStateData", sizeof(CommWriteStateData));
    conn_close_pool = memPoolCreate("close_handler", sizeof(close_handler));
#if DELAY_POOLS
    slow_wfds = xcalloc(sizeof(int), Squid_MaxFD);
    slow_wfds_alt = xcalloc(sizeof(int), Squid_MaxFD);
    slow_wfds_entry = xcalloc(sizeof(int), Squid_MaxFD);
    for (i = 0; i < Squid_MaxFD; i++) {
	slow_wfds_entry[i] = -1;
    }


    eventAdd("comm_slow_wfds_wakeup_event", comm_slow_wfds_wakeup_event, NULL, 1.0, 128);
#endif
}
