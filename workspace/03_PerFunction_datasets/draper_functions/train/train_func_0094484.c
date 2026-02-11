efreet_cache_desktop_find(const char *file)
{
    Efreet_Cache_Desktop *cache;
    char rp[PATH_MAX];

    if (!realpath(file, rp)) return NULL;

    if (!efreet_cache_check(&desktop_cache, efreet_desktop_cache_file(), EFREET_DESKTOP_CACHE_MAJOR)) return NULL;

    cache = eina_hash_find(desktops, rp);
    if (cache == NON_EXISTING) return NULL;
    if (cache)
    {

        if ((ecore_time_get() - cache->check_time) < 1)
        {
            INF("Return without stat %f %f", ecore_time_get(), cache->check_time);
            return &cache->desktop;
        }
        if (cache->desktop.load_time == ecore_file_mod_time(cache->desktop.orig_path))
        {
            INF("Return with stat %f %f", ecore_time_get(), cache->check_time);
            cache->check_time = ecore_time_get();
            return &cache->desktop;
        }


        eina_hash_set(desktops, rp, NON_EXISTING);
        cache = NULL;
    }

    cache = eet_data_read(desktop_cache, efreet_desktop_edd(), rp);
    if (cache)
    {
        if (cache->desktop.load_time != ecore_file_mod_time(cache->desktop.orig_path))
        {

            INF("We got stale data in the desktop cache");
            efreet_cache_desktop_free(&cache->desktop);
            eina_hash_set(desktops, rp, NON_EXISTING);
        }
        else
        {
            cache->desktop.eet = 1;
            cache->check_time = ecore_time_get();
            eina_hash_set(desktops, cache->desktop.orig_path, cache);
            return &cache->desktop;
        }
    }
    else
        eina_hash_set(desktops, rp, NON_EXISTING);
    return NULL;
}
