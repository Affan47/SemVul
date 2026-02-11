uprv_normalizer2_cleanup() {
    delete nfcSingleton;
    nfcSingleton = NULL;
    delete nfkcSingleton;
    nfkcSingleton = NULL;
    delete nfkc_cfSingleton;
    nfkc_cfSingleton = NULL;
    delete noopSingleton;
    noopSingleton = NULL;
    uhash_close(cache);
    cache=NULL;
    nfcInitOnce.reset();
    nfkcInitOnce.reset();
    nfkc_cfInitOnce.reset();
    noopInitOnce.reset();
    return TRUE;
}
