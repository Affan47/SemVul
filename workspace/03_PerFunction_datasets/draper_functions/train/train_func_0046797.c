alloc_table(VLC *vlc, int size, int use_static)
{
    int index;
    index = vlc->table_size;
    vlc->table_size += size;
    if (vlc->table_size > vlc->table_allocated) {
        if(use_static>1)
            abort();
        vlc->table_allocated += (1 << vlc->bits);
        if(use_static)
            vlc->table = ff_realloc_static(vlc->table,
                                           sizeof(VLC_TYPE) * 2 * vlc->table_allocated);
        else
            vlc->table = av_realloc(vlc->table,
                                    sizeof(VLC_TYPE) * 2 * vlc->table_allocated);
        if (!vlc->table)
            return -1;
    }
    return index;
}
