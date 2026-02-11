create_network_list(GtkTreeModel *model,
                    GtkWidget **scroll)
{
    static const GwyEnum columns[] = {
        { N_("Name"),   NETWORK_NAME,   },
        { N_("Size"),   NETWORK_SIZE,   },
        { N_("Hidden"), NETWORK_HIDDEN, },
    };

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkWidget *networklist;
    guint i;

    networklist = gtk_tree_view_new_with_model(model);
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(networklist), TRUE);

    for (i = 0; i < G_N_ELEMENTS(columns); i++) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(_(columns[i].name),
                                                          renderer,
                                                          NULL);
        gtk_tree_view_column_set_cell_data_func
                                         (column, renderer,
                                          network_cell_renderer,
                                          GUINT_TO_POINTER(columns[i].value),
                                          NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(networklist), column);
    }

    *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scroll),
                                   GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(*scroll), networklist);

    return networklist;
}
