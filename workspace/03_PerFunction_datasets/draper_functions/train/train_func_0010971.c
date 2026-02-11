on_renderer_combo_changed (GtkComboBox *widget,
                           gpointer     user_data)
{
        GtkComboBox  *combo;
        GtkTreeModel *model;
        GtkTreeIter   iter;
        PlaybackState state;
        guint         volume;

        combo = GTK_COMBO_BOX (renderer_combo);
        model = gtk_combo_box_get_model (combo);
        g_assert (model != NULL);

        if (!gtk_combo_box_get_active_iter (combo, &iter)) {
                return;
        }

        gtk_tree_model_get (model,
                            &iter,
                            6, &state,
                            7, &volume,
                            -1);
        set_volume_hscale (volume);
        prepare_controls_for_state (state);
}
