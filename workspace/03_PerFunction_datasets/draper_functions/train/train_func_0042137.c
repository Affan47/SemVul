storeCleanup(void *datanotused)
{
    static int bucketnum = -1;
    static int validnum = 0;
    static int store_errors = 0;
    int validnum_start;
    StoreEntry *e;
    hash_link *link_ptr = NULL;
    hash_link *link_next = NULL;
    int limit = opt_foreground_rebuild ? 1 << 30 : 500;
    validnum_start = validnum;

    while (validnum - validnum_start < limit) {
	if (++bucketnum >= store_hash_buckets) {
	    debug(20, 1) ("  Completed Validation Procedure\n");
	    debug(20, 1) ("  Validated %d Entries\n", validnum);
	    debug(20, 1) ("  store_swap_size = %dk\n", store_swap_size);
	    store_dirs_rebuilding--;
	    assert(0 == store_dirs_rebuilding);
	    if (opt_store_doublecheck)
		assert(store_errors == 0);
	    if (store_digest)
		storeDigestNoteStoreReady();
	    return;
	}
	link_next = hash_get_bucket(store_table, bucketnum);
	while (NULL != (link_ptr = link_next)) {
	    link_next = link_ptr->next;
	    e = (StoreEntry *) link_ptr;
	    if (EBIT_TEST(e->flags, ENTRY_VALIDATED))
		continue;


	    if (e->swap_filen < 0)
		continue;
	    if (opt_store_doublecheck)
		if (storeCleanupDoubleCheck(e))
		    store_errors++;
	    EBIT_SET(e->flags, ENTRY_VALIDATED);


	    storeDirUpdateSwapSize(&Config.cacheSwap.swapDirs[e->swap_dirn], e->swap_file_sz, 1);

	    if (EBIT_TEST(e->flags, KEY_PRIVATE))
		storeRelease(e);
	    if ((++validnum & 0x3FFFF) == 0)
		debug(20, 1) ("  %7d Entries Validated so far.\n", validnum);
	}
    }
    eventAdd("storeCleanup", storeCleanup, NULL, 0.0, 1);
}
