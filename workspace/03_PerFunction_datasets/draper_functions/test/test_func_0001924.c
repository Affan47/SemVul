_fm_vfs_search_enumerator_close(GFileEnumerator *enumerator,
                                              GCancellable *cancellable,
                                              GError **error)
{
    FmVfsSearchEnumerator *enu = FM_VFS_SEACRH_ENUMERATOR(enumerator);
    FmSearchIntIter *iter;

    while((iter = enu->iter))
    {
        enu->iter = iter->parent;
        _search_iter_free(iter, cancellable);
    }
    return TRUE;
}
