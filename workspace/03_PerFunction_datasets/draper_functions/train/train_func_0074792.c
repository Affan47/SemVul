on_button_config_layouts_add_clicked (GtkButton *button, gpointer data)
{
    InputPadGtkWindow *window;
    GtkWidget *combobox;
    GtkWidget *add_treeview;
    GtkWidget *remove_treeview;
    GtkTreeModel *combo_model;
    GtkTreeModel *add_model;
    GtkTreeModel *remove_model;
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    gchar *layout_name = NULL;
    gchar *layout_desc = NULL;
    gchar *variant_name = NULL;
    gchar *variant_desc = NULL;

    g_return_if_fail (data != NULL &&
                      INPUT_PAD_IS_GTK_WINDOW (data));

    window = INPUT_PAD_GTK_WINDOW (data);
    combobox = window->priv->config_layouts_combobox;
    add_treeview = window->priv->config_layouts_add_treeview;
    combo_model = gtk_combo_box_get_model (GTK_COMBO_BOX (combobox));
    remove_treeview = window->priv->config_layouts_remove_treeview;
    remove_model = gtk_tree_view_get_model (GTK_TREE_VIEW (remove_treeview));
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (add_treeview));

    if (!gtk_tree_selection_get_selected (selection, &add_model, &iter)) {
        return;
    }

    gtk_tree_model_get (add_model, &iter,
                        LAYOUT_LAYOUT_NAME_COL,
                        &layout_name,
                        LAYOUT_LAYOUT_DESC_COL,
                        &layout_desc,
                        LAYOUT_VARIANT_NAME_COL,
                        &variant_name,
                        LAYOUT_VARIANT_DESC_COL,
                        &variant_desc,
                        -1);
    config_layouts_list_remove_iter (GTK_LIST_STORE (add_model), &iter);
    config_layouts_list_append_layout (GTK_LIST_STORE (remove_model),
                                       layout_name, layout_desc,
                                       variant_name, variant_desc);
    gtk_tree_store_append (GTK_TREE_STORE (combo_model), &iter, NULL);
    gtk_tree_store_set (GTK_TREE_STORE (combo_model), &iter,
                        LAYOUT_LAYOUT_NAME_COL,
                        g_strdup (layout_name),
                        LAYOUT_LAYOUT_DESC_COL,
                        variant_desc ? g_strdup (variant_desc) :
                            g_strdup (layout_desc),
                        LAYOUT_VARIANT_NAME_COL,
                        g_strdup (variant_name),
                        LAYOUT_VARIANT_DESC_COL, NULL,
                        LAYOUT_VISIBLE_COL, TRUE, -1);
    g_free (layout_name);
    g_free (layout_desc);
    g_free (variant_name);
    g_free (variant_desc);
}
