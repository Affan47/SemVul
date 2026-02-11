file_close(DISK_FILE *df) {
    if(!df)
        return;
#ifdef USE_WIN32
    CloseHandle(df->fh);
#else
    close(df->fd);
#endif
    str_free(df);
}
