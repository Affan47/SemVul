fm_folder_view_set_model(FmFolderView* fv, FmFolderModel* model)
{
    FmFolderViewInterface* iface;
    FmFolderModel* old_model;
    FmFolderModelCol by = FM_FOLDER_MODEL_COL_DEFAULT;
    FmSortMode mode = FM_SORT_ASCENDING;

    g_return_if_fail(FM_IS_FOLDER_VIEW(fv));

    iface = FM_FOLDER_VIEW_GET_IFACE(fv);
    old_model = iface->get_model(fv);
    if(old_model)
    {
        fm_folder_model_get_sort(old_model, &by, &mode);
        unset_model(fv, old_model);


        iface->unselect_all(fv);
    }

    iface->set_model(fv, model);
    if(model)
    {
        fm_folder_model_set_sort(model, by, mode);
        g_signal_connect(model, "sort-column-changed", G_CALLBACK(on_sort_col_changed), fv);
        g_signal_connect(model, "filter-changed", G_CALLBACK(on_filter_changed), fv);
    }
}
