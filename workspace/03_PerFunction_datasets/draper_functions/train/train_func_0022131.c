storeRecycle(StoreEntry * e)
{
    if (e->swap_dirn >= 0 && !storeEntryLocked(e)) {
	SwapDir *SD = INDEXSD(e->swap_dirn);


	storeExpireNow(e);
	storeReleaseRequest(e);


	SD->obj.recycle(SD, e);
    }

    storeRelease(e);
}
