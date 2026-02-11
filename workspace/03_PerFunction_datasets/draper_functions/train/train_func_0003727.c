storeSwapInFileNotify(void *data, int errflag, storeIOState * sio)
{
    store_client *sc = data;
    StoreEntry *e = sc->entry;

    debug(1, 3) ("storeSwapInFileNotify: changing %d/%d to %d/%d\n", e->swap_filen, e->swap_dirn, sio->swap_filen, sio->swap_dirn);

    e->swap_filen = sio->swap_filen;
    e->swap_dirn = sio->swap_dirn;
}
