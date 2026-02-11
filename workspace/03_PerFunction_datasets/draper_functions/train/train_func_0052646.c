storeMaintainSwapSpace(void *datanotused)
{
    int i;
    SwapDir *SD;
    static time_t last_warn_time = 0;


    for (i = 0; i < Config.cacheSwap.n_configured; i++) {

	SD = INDEXSD(i);


	if (SD->maintainfs != NULL)
	    SD->maintainfs(SD);
    }
    if (store_swap_size > Config.Swap.maxSize) {
	if (squid_curtime - last_warn_time > 10) {
	    debug(20, 0) ("WARNING: Disk space over limit: %ld KB > %ld KB\n",
		(long int) store_swap_size, (long int) Config.Swap.maxSize);
	    last_warn_time = squid_curtime;
	}
    }

    eventAdd("MaintainSwapSpace", storeMaintainSwapSpace, NULL, 1.0, 1);
}
