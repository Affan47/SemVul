cb_update_disks(gpointer data)
{
    ProcmanApp *app = static_cast<ProcmanApp *>(data);
    GtkListStore *list;
    glibtop_mountentry * entries;
    glibtop_mountlist mountlist;
    guint i;

    list = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(app->disk_list)));

    entries = glibtop_get_mountlist(&mountlist, app->config.show_all_fs);

    remove_old_disks(GTK_TREE_MODEL(list), entries, mountlist.number);

    for (i = 0; i < mountlist.number; i++)
        add_disk(list, &entries[i], app->config.show_all_fs);

    g_free(entries);

    return TRUE;
}
