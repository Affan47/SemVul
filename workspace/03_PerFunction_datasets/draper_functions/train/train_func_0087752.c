_fm_folder_event_file_added(FmFolder *folder, FmPath *path)
{
    gboolean added = TRUE;

    G_LOCK(lists);

    if(!g_slist_find(folder->files_to_add, path))
    {
        GList *l = _fm_folder_get_file_by_path(folder, path);
        if(!l)
        {

            folder->files_to_add = g_slist_append(folder->files_to_add, path);
        }
        else if(g_slist_find(folder->files_to_update, path))
        {

            added = FALSE;
        }

        else
        {


            folder->files_to_del = g_slist_remove(folder->files_to_del, l);

            folder->files_to_update = g_slist_append(folder->files_to_update, path);
        }
    }
    else

        added = FALSE;
    if(added && !folder->idle_handler)
        folder->idle_handler = g_idle_add_full(G_PRIORITY_LOW, (GSourceFunc)on_idle, folder, NULL);
    G_UNLOCK(lists);
    return added;
}
