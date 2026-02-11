ario_server_preferences_new (void)
{
        ARIO_LOG_FUNCTION_START;
        ArioServerPreferences *server_preferences;
        GtkBuilder *builder;
        ArioServer *server = ario_server_get_instance ();

        server_preferences = g_object_new (TYPE_ARIO_SERVER_PREFERENCES,
                                           NULL);

        g_return_val_if_fail (server_preferences->priv != NULL, NULL);

        g_signal_connect_object (server,
                                 "state_changed",
                                 G_CALLBACK (ario_server_preferences_server_changed_cb),
                                 server_preferences, 0);
        g_signal_connect_object (server,
                                 "updatingdb_changed",
                                 G_CALLBACK (ario_server_preferences_server_changed_cb),
                                 server_preferences, 0);

        builder = gtk_builder_helpers_new (UI_PATH "server-prefs.ui",
                                           server_preferences);

        server_preferences->priv->crossfade_checkbutton =
                GTK_WIDGET (gtk_builder_get_object (builder, "crossfade_checkbutton"));
        server_preferences->priv->crossfadetime_spinbutton =
                GTK_WIDGET (gtk_builder_get_object (builder, "crossfadetime_spinbutton"));
        server_preferences->priv->updatedb_label =
                GTK_WIDGET (gtk_builder_get_object (builder, "updatedb_label"));
        server_preferences->priv->updatedb_button =
                GTK_WIDGET (gtk_builder_get_object (builder, "updatedb_button"));
        server_preferences->priv->update_checkbutton =
                GTK_WIDGET (gtk_builder_get_object (builder, "update_checkbutton"));
        server_preferences->priv->stopexit_checkbutton =
                GTK_WIDGET (gtk_builder_get_object (builder, "stopexit_checkbutton"));
        server_preferences->priv->outputs_model =
                GTK_LIST_STORE (gtk_builder_get_object (builder, "outputs_model"));

        gtk_builder_helpers_boldify_label (builder, "crossfade_frame_label");
        gtk_builder_helpers_boldify_label (builder, "database_frame_label");
        gtk_builder_helpers_boldify_label (builder, "ouputs_frame_label");

        ario_server_preferences_sync_server (server_preferences);

        gtk_box_pack_start (GTK_BOX (server_preferences), GTK_WIDGET (gtk_builder_get_object (builder, "vbox")), TRUE, TRUE, 0);

        g_object_unref (builder);

        return GTK_WIDGET (server_preferences);
}
