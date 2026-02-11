storeOpen(StoreEntry * e, STFNCB * file_callback, STIOCB * callback,
    void *callback_data)
{
    int load;
    storeIOState *sio;

    SwapDir *SD = &Config.cacheSwap.swapDirs[e->swap_dirn];
    store_io_stats.open.calls++;
    load = SD->checkload(SD, ST_OP_OPEN);
    if (load < 0 || load > 1000) {
	store_io_stats.open.loadav_fail++;
	return NULL;
    }
    sio = SD->obj.open(SD, e, file_callback, callback, callback_data);
    if (sio == NULL) {
	store_io_stats.open.open_fail++;
    } else {
	store_io_stats.open.success++;
    }
    return sio;
}
