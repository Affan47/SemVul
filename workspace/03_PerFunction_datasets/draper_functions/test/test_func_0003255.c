device_selection_btn_clicked_cb (GtkButton *btn, SyncConfigWidget *self)
{
    GtkTreeIter iter;

    if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (self->combo), &iter)) {
        const char *name;
        SyncevoConfig *config;
        GtkTreeModel *model;

        self->device_template_selected = TRUE;

        model = gtk_combo_box_get_model(GTK_COMBO_BOX (self->combo));
        gtk_tree_model_get (model, &iter, 0, &name, -1 );
        gtk_tree_model_get (model, &iter, 1, &config, -1 );

        sync_config_widget_set_config (self, config);

        sync_config_widget_update_expander (self);
    }
}
