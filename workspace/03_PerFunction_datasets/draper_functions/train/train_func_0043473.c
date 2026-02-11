on_window_keyboard_changed_combobox (InputPadGtkWindow *window,
                                     gint               group,
                                     gpointer           data)
{
    GtkTreeModel *model;
    GtkTreeIter   active_iter;
    GtkTreeIter   iter;
    gchar **group_layouts;
    gchar *active_layout = NULL;
    gchar *layout;
    gchar *desc;

    g_return_if_fail (window != NULL &&
                      INPUT_PAD_IS_GTK_WINDOW (window));

    if ((group_layouts = window->priv->group_layouts) == NULL) {
        return;
    }

    g_return_if_fail (data != NULL &&
                      GTK_IS_COMBO_BOX (data));

    model = gtk_combo_box_get_model (GTK_COMBO_BOX (data));
    if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (data), &active_iter)) {
        gtk_tree_model_get (model, &active_iter,
                            LAYOUT_LAYOUT_NAME_COL, &active_layout, -1);
    }
    if (!gtk_tree_model_get_iter_first (model, &iter)) {
        g_warning ("Could not get the first iter in layout combo box");
        g_free (active_layout);
        return;
    }
    do {
        gtk_tree_model_get (model, &iter,
                            LAYOUT_LAYOUT_NAME_COL, &layout,
                            LAYOUT_LAYOUT_DESC_COL, &desc, -1);
        if (!g_strcmp0 (group_layouts[group], layout) &&
            (g_strcmp0 (active_layout, layout) != 0)) {
            gtk_combo_box_set_active_iter (GTK_COMBO_BOX (data), &iter);
            g_free (layout);
            g_free (desc);
            break;
        }
        g_free (layout);
        g_free (desc);
    } while (gtk_tree_model_iter_next (model, &iter));
    g_free (active_layout);
}
