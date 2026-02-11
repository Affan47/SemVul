ram_remove(Store *store, const char *filename)
{
    RAMFile *rf = (RAMFile *)h_rem(store->dir.ht, filename, false);
    if (rf != NULL) {
        DEREF(rf);
        rf_close(rf);
        return true;
    }
    else {
        return false;
    }
}
