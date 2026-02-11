uaesrand (uae_u32 seed) {
	oldhcounter = -1;
	randseed = seed;

    if (g_random_debug_logging) {
        write_log (_T("seed=%08x\n"), randseed);
    }
	return randseed;
}
