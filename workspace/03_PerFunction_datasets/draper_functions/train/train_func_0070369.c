get_selected_renderer_volume (void)
{
        GtkComboBox  *combo;
        GtkTreeModel *model;
        GtkTreeIter   iter;
        guint         volume;

        combo = GTK_COMBO_BOX (renderer_combo);
        model = gtk_combo_box_get_model (combo);
        g_assert (model != NULL);

        if (!gtk_combo_box_get_active_iter (combo, &iter)) {
                return 0;
        }

        gtk_tree_model_get (model,
                            &iter,
                            7, &volume,
                            -1);

        return volume;
}
