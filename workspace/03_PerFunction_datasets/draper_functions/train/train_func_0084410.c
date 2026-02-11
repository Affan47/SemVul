get_bookmark_drag_dest(FmPlacesView* view, GtkTreePath** tp, GtkTreeViewDropPosition* pos)
{
    gboolean ret = TRUE;
    if(*tp)
    {

        if(fm_places_model_path_is_bookmark(model, *tp))
        {

            if(*pos == GTK_TREE_VIEW_DROP_INTO_OR_BEFORE ||
               *pos == GTK_TREE_VIEW_DROP_INTO_OR_AFTER)
                ret = FALSE;
            else
                ret = TRUE;
        }
        else
        {
            GtkTreePath* sep = fm_places_model_get_separator_path(model);

            gtk_tree_path_get_indices(*tp)[0] = gtk_tree_path_get_indices(sep)[0] + 1;
            gtk_tree_path_free(sep);
            *pos = GTK_TREE_VIEW_DROP_BEFORE;
            ret = TRUE;
        }
    }
    else
    {

        *tp = gtk_tree_path_new_from_indices(gtk_tree_model_iter_n_children(GTK_TREE_MODEL(model), NULL) - 1, -1);
        *pos = GTK_TREE_VIEW_DROP_AFTER;
        ret = TRUE;
    }

    return ret;
}
