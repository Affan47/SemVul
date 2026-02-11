_fm_vfs_search_get_uri(GFile *file)
{
    FmSearchVFile *item = FM_SEARCH_VFILE(file);

    if(item->current)
        return g_file_get_uri(item->current);
    return g_strdup(item->path);
}
