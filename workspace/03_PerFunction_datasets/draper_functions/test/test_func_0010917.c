rename_group_menu_cb(GtkWidget *widget, HybridGroup *group)
{
    GtkTreeView  *tree;
    GtkTreeModel *model;
    GtkTreePath  *path;

    if (!hybrid_blist_get_group_renamable(group)) {

        return;
    }

    tree  = GTK_TREE_VIEW(blist->treeview);
    model = gtk_tree_view_get_model(tree);
    path  = gtk_tree_model_get_path(model, &group->iter);
    if (!G_IS_OBJECT(blist->text_renderer)) {
        hybrid_debug_error("blist", "text_renderer is not a valid gtk object.");
        return;
    }
    g_object_set(blist->text_renderer, "editable", TRUE, NULL);

    gtk_widget_grab_focus(blist->treeview);
    gtk_tree_view_set_cursor_on_cell(GTK_TREE_VIEW(blist->treeview), path,
            blist->text_column, blist->text_renderer, TRUE);
    gtk_tree_path_free(path);
}
