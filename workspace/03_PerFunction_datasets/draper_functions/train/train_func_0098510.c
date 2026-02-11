clear_file_cache(void)
{
        int i;

        if (DUMPFILE())
                return;

        for (i = 0; i < DENTRY_CACHE; i++) {
                ft->cached_file[i] = 0;
                ft->cached_file_hits[i] = 0;
        }

        ft->file_cache_fills = 0;
        ft->file_cache_index = 0;
}
