ldbm_back_monitor_search(Slapi_PBlock *pb, Slapi_Entry *e,
    Slapi_Entry *entryAfter, int *returncode, char *returntext, void *arg)
{
    struct ldbminfo *li = (struct ldbminfo *)arg;
    struct berval val;
    struct berval *vals[2];
    char buf[BUFSIZ];
    DB_MPOOL_STAT *mpstat = NULL;
    DB_MPOOL_FSTAT **mpfstat = NULL;
    u_int32_t cache_tries;

    vals[0] = &val;
    vals[1] = NULL;


    PR_snprintf(buf, sizeof(buf), "%s", li->li_plugin->plg_name);
    MSET("database");


    if (dblayer_memp_stat(li, &mpstat, &mpfstat) != 0) {
        *returncode = LDAP_OPERATIONS_ERROR;
        return SLAPI_DSE_CALLBACK_ERROR;
    }


    sprintf(buf, "%lu", (unsigned long)mpstat->st_cache_hit);
    MSET("dbCacheHits");


    cache_tries = (mpstat->st_cache_miss + mpstat->st_cache_hit);
    sprintf(buf, "%u", cache_tries);
    MSET("dbCacheTries");


    sprintf(buf, "%lu", (unsigned long)(100.0 * (double)mpstat->st_cache_hit / (double)(cache_tries > 0 ? cache_tries : 1) ));
    MSET("dbCacheHitRatio");

    sprintf(buf, "%lu", (unsigned long)mpstat->st_page_in);
    MSET("dbCachePageIn");
    sprintf(buf, "%lu", (unsigned long)mpstat->st_page_out);
    MSET("dbCachePageOut");
    sprintf(buf, "%lu", (unsigned long)mpstat->st_ro_evict);
    MSET("dbCacheROEvict");
    sprintf(buf, "%lu", (unsigned long)mpstat->st_rw_evict);
    MSET("dbCacheRWEvict");

    slapi_ch_free((void **)&mpstat);

    if (mpfstat) {
#if 1000*DB_VERSION_MAJOR + 100*DB_VERSION_MINOR + DB_VERSION_PATCH <= 3204

        int i;
        for (i = 0; mpfstat[i]; i++)
            slapi_ch_free((void **)&mpfstat[i]);
#endif
        slapi_ch_free((void **)&mpfstat);
    }

    *returncode = LDAP_SUCCESS;
    return SLAPI_DSE_CALLBACK_OK;
}
