parasite_widget_tree_select_widget(ParasiteWidgetTree *widget_tree,
                                   GtkWidget *widget)
{
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(widget_tree));
    GList *parents = get_parents(widget, NULL);
    GList *l;
    GtkTreeIter iter, parent_iter = {0};
    gboolean found = FALSE;
    gboolean in_root = TRUE;

    for (l = parents; l != NULL; l = l->next)
    {
        GtkWidget *cur_widget = GTK_WIDGET(l->data);
        gboolean valid;
        found = FALSE;

        for (valid = gtk_tree_model_iter_children(model, &iter,
                                                  in_root ? NULL
                                                  : &parent_iter);
              valid;
              valid = gtk_tree_model_iter_next(model, &iter))
        {
            GtkWidget *iter_widget;

            gtk_tree_model_get(model, &iter,
                               WIDGET, &iter_widget,
                               -1);

            if (iter_widget == cur_widget)
            {
                parent_iter = iter;
                in_root = FALSE;
                found = TRUE;
                break;
            }
        }

        if (!found)
        {

            break;
        }
    }

    if (found)
    {
        GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
        gtk_tree_view_expand_to_path(GTK_TREE_VIEW(widget_tree), path);
        gtk_tree_selection_select_iter(
            gtk_tree_view_get_selection(GTK_TREE_VIEW(widget_tree)),
            &iter);
        gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(widget_tree), path, NULL,
                                     FALSE, 0, 0);
    }

    g_list_free(parents);
}
