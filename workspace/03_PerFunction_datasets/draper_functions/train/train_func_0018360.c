on_dir_list_finished(GObject *source_object, GAsyncResult *res,
                                 gpointer user_data)
#else
static gboolean on_dir_list_finished(gpointer user_data)
#endif
{
    ListSubDirNames* data = (ListSubDirNames*)user_data;
    FmPathEntry* entry = data->entry;
    FmPathEntryPrivate *priv  = FM_PATH_ENTRY_GET_PRIVATE(entry);
    GList* l;
    FmPathEntryModel* new_model;


    if(g_cancellable_is_cancelled(data->cancellable))
#if GLIB_CHECK_VERSION(2, 36, 0)
        return;
#else
        return TRUE;
#endif


    new_model = fm_path_entry_model_new(priv->parent_dir);


    for(l = data->subdirs; l; l=l->next)
    {
        char* name = l->data;
        gtk_list_store_insert_with_values((GtkListStore*)new_model, NULL, -1, COL_BASENAME, name, -1);
    }
    priv->folder_loaded = TRUE;
    priv->long_list = (g_list_length(data->subdirs) > 40);

    gtk_entry_completion_set_model(priv->completion, GTK_TREE_MODEL(new_model));
    if(priv->model)
        g_object_unref(priv->model);
    priv->model = new_model;


    update_inline_completion(priv);
    gtk_entry_completion_insert_prefix(priv->completion);
    gtk_entry_completion_complete(priv->completion);


    g_signal_emit_by_name(entry, "changed", 0);
#if !GLIB_CHECK_VERSION(2, 36, 0)
    return TRUE;
#endif
}
