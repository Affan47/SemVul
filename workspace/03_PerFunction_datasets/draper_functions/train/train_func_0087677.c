storeDirSwapLog(const StoreEntry * e, int op)
{
    SwapDir *sd;
    assert(!EBIT_TEST(e->flags, KEY_PRIVATE));
    assert(e->swap_filen >= 0);


    if (EBIT_TEST(e->flags, ENTRY_SPECIAL))
	return;
    assert(op > SWAP_LOG_NOP && op < SWAP_LOG_MAX);
    debug(20, 3) ("storeDirSwapLog: %s %s %d %08X\n",
	swap_log_op_str[op],
	storeKeyText(e->hash.key),
	e->swap_dirn,
	e->swap_filen);
    sd = &Config.cacheSwap.swapDirs[e->swap_dirn];
    (sd->log.write) (sd, e, op);
}
