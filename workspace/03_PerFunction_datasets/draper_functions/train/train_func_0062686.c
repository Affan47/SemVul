gx_char_cache_init(register gs_font_dir * dir)
{
    int i;
    cached_fm_pair *pair;
    char_cache_chunk *cck = (char_cache_chunk *)
    gs_alloc_bytes_immovable(dir->ccache.bits_memory,
                             sizeof(char_cache_chunk),
                             "initial_chunk");
    if (cck == NULL)
        return_error(gs_error_VMerror);

    dir->fmcache.msize = 0;
    dir->fmcache.used = dir->fmcache.mmax;
    dir->fmcache.free = dir->fmcache.mmax;
    dir->fmcache.unused = 0;
    gx_bits_cache_chunk_init(cck, NULL, 0);
    gx_bits_cache_init((gx_bits_cache *) & dir->ccache, cck);
    dir->ccache.bspace = 0;
    memset((char *)dir->ccache.table, 0,
           (dir->ccache.table_mask + 1) * sizeof(cached_char *));
    for (i = 0, pair = dir->fmcache.mdata;
         i < dir->fmcache.mmax; i++, pair++) {
        pair->index = i;
        fm_pair_init(pair);
        pair->ttf = 0;
        pair->ttr = 0;
    }
    return 0;
}
