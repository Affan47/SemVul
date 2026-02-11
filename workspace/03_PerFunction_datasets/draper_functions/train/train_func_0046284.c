free_keymanagers(void)
{   keymanager_t *km;

    for (km=keymgrs; km!=NULL; km=km->next) {
        if ((km->initialized & KM_INIT_ALGS) != 0) {
            km->free_algs();
            km->initialized = 0;
        }
    }

    return 0;
}
