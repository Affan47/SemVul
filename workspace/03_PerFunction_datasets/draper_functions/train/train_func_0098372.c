on_matcher_ok_clicked (GtkButton *button,
                       GNCImportMainMatcher *info)
{
    GtkTreeModel *model;
    GtkTreePath *path;
    GtkTreeRowReference *ref;
    GtkTreeIter iter;
    GNCImportTransInfo *trans_info;
    GSList *refs_list = NULL;

    g_assert (info);


    model = gtk_tree_view_get_model(info->view);
    if (!gtk_tree_model_get_iter_first(model, &iter))
        return;


    gnc_suspend_gui_refresh();

    do
    {
        gtk_tree_model_get(model, &iter,
                           DOWNLOADED_COL_DATA, &trans_info,
                           -1);

        if (gnc_import_process_trans_item(NULL, trans_info))
        {
            path = gtk_tree_model_get_path(model, &iter);
            ref = gtk_tree_row_reference_new(model, path);
            refs_list = g_slist_append(refs_list, ref);
            gtk_tree_path_free(path);

            if (info->transaction_processed_cb)
            {
                info->transaction_processed_cb(trans_info,
                                               TRUE,
                                               info->user_data);
            }
        }
    }
    while (gtk_tree_model_iter_next (model, &iter));


    gnc_resume_gui_refresh();

    gnc_gen_trans_list_delete (info);

}
