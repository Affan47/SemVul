on_row_inserted(GtkTreeModel *tree_model, GtkTreePath *path,
                            GtkTreeIter *iter, FmStandardView* fv)
{
    if(fv->mode == FM_FV_LIST_VIEW)
        _reset_columns_widths(GTK_TREE_VIEW(fv->view));
}
