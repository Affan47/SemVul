_fm_standard_view_get_columns(FmFolderView* fv)
{
    FmStandardView* view;
    GSList* list;
    GList *cols_list, *ld;

    if(!FM_IS_STANDARD_VIEW(fv))
        return NULL;
    view = (FmStandardView*)fv;

    if(view->mode != FM_FV_LIST_VIEW)
        return NULL;

    cols_list = gtk_tree_view_get_columns(GTK_TREE_VIEW(view->view));
    if(cols_list == NULL)
        return NULL;
    list = NULL;
    for(ld = cols_list; ld; ld = ld->next)
    {
        GtkTreeViewColumn *col = ld->data;
        FmFolderViewColumnInfo* info = g_object_get_qdata(G_OBJECT(col), fm_qdata_id);
        list = g_slist_append(list, info);
    }
    g_list_free(cols_list);
    return list;
}
