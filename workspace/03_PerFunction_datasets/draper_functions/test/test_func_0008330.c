hcache_timer(void *unused_obj)
{
	time_t now = tm_time();

	(void) unused_obj;

    hcache_expire_all(now);

    if (GNET_PROPERTY(hcache_debug) >= 15) {
        hcache_dump_info(caches[HCACHE_FRESH_ANY],   "timer");
        hcache_dump_info(caches[HCACHE_VALID_ANY],   "timer");

        hcache_dump_info(caches[HCACHE_FRESH_ULTRA], "timer");
        hcache_dump_info(caches[HCACHE_VALID_ULTRA], "timer");

        hcache_dump_info(caches[HCACHE_FRESH_ULTRA6], "timer");
        hcache_dump_info(caches[HCACHE_VALID_ULTRA6], "timer");

        hcache_dump_info(caches[HCACHE_GUESS],        "timer");
        hcache_dump_info(caches[HCACHE_GUESS_INTRO],  "timer");

        hcache_dump_info(caches[HCACHE_GUESS6],       "timer");
        hcache_dump_info(caches[HCACHE_GUESS6_INTRO], "timer");

        hcache_dump_info(caches[HCACHE_TIMEOUT],  "timer");
        hcache_dump_info(caches[HCACHE_BUSY],     "timer");
        hcache_dump_info(caches[HCACHE_UNSTABLE], "timer");

        g_debug("HCACHE global: local %u   alrdy connected %u   invalid %u",
            stats[HCACHE_LOCAL_INSTANCE], stats[HCACHE_ALREADY_CONNECTED],
            stats[HCACHE_INVALID_HOST]);
    }

	return TRUE;
}
