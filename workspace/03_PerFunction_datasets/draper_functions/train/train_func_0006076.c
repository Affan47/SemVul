efreet_cache_init(void)
{
    char buf[PATH_MAX];

    _efreet_cache_log_dom = eina_log_domain_register("efreet_cache", EFREET_DEFAULT_LOG_COLOR);
    if (_efreet_cache_log_dom < 0)
        return 0;

    EFREET_EVENT_ICON_CACHE_UPDATE = ecore_event_type_new();
    EFREET_EVENT_DESKTOP_CACHE_UPDATE = ecore_event_type_new();
    EFREET_EVENT_DESKTOP_CACHE_BUILD = ecore_event_type_new();

    themes = eina_hash_string_superfast_new(EINA_FREE_CB(efreet_cache_icon_theme_free));
    icons = eina_hash_string_superfast_new(EINA_FREE_CB(efreet_cache_icon_free));
    fallbacks = eina_hash_string_superfast_new(EINA_FREE_CB(efreet_cache_icon_fallback_free));
    desktops = eina_hash_string_superfast_new(NULL);

    if (efreet_cache_update)
    {
        snprintf(buf, sizeof(buf), "%s/efreet", efreet_cache_home_get());
        if (!ecore_file_exists(buf))
        {
            if (!ecore_file_mkpath(buf))
            {
                ERR("Failed to create directory '%s'", buf);
                goto error;
            }
            efreet_setowner(buf);
        }

        cache_exe_handler = ecore_event_handler_add(ECORE_EXE_EVENT_DEL,
                                                    cache_exe_cb, NULL);
        if (!cache_exe_handler)
        {
            ERR("Failed to add exe del handler");
            goto error;
        }

        cache_monitor = ecore_file_monitor_add(buf,
                                               cache_update_cb,
                                               NULL);
        if (!cache_monitor)
        {
            ERR("Failed to set up ecore file monitor for '%s'", buf);
            goto error;
        }

        efreet_cache_icon_update();
        efreet_cache_desktop_update();
    }

    return 1;
error:
    if (themes) eina_hash_free(themes);
    themes = NULL;
    if (icons) eina_hash_free(icons);
    icons = NULL;
    if (fallbacks) eina_hash_free(fallbacks);
    fallbacks = NULL;
    if (desktops) eina_hash_free(desktops);
    desktops = NULL;

    if (cache_exe_handler) ecore_event_handler_del(cache_exe_handler);
    cache_exe_handler = NULL;
    if (cache_monitor) ecore_file_monitor_del(cache_monitor);
    cache_monitor = NULL;
    efreet_cache_edd_shutdown();
    return 0;
}
