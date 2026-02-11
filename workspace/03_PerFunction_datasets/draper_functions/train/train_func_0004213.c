amiga_set_synchronization_log_file(const char *path) {
#ifdef DEBUG_SYNC
    FILE *f = fs_fopen(path, "wb");
    if (f) {
        write_log("sync debug log to %s\n", path);
        g_fs_uae_sync_debug_file = f;
        return 1;
    }
    else {
        write_log("error opening synchronization log file\n");
        return 0;
    }
#endif
}
