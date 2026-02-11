ui_init (void)
{
        GObject *object;
        gchar *filename;
        GError *error = NULL;


        initialized = TRUE;

        manager = gtk_ui_manager_new ();

        filename = gva_find_data_file (PACKAGE ".builder");
        if (filename != NULL && error == NULL)
        {
                builder = gtk_builder_new ();
                gtk_builder_add_from_file (builder, filename, &error);
                gtk_builder_connect_signals (builder, NULL);
        }
        g_free (filename);

        filename = gva_find_data_file (PACKAGE ".ui");
        if (filename != NULL && error == NULL)
        {
                gtk_window_add_accel_group (
                        GTK_WINDOW (GVA_WIDGET_MAIN_WINDOW),
                        gtk_ui_manager_get_accel_group (manager));

                g_signal_connect (
                        manager, "connect-proxy",
                        G_CALLBACK (gva_main_connect_proxy_cb), NULL);

                gtk_ui_manager_add_ui_from_file (manager, filename, &error);
        }
        g_free (filename);

        if (error != NULL)
                g_error ("%s", error->message);

        if (builder == NULL || manager == NULL)
                g_error ("%s", _("Failed to initialize user interface"));

        object = gtk_builder_get_object (builder, "standard-actions");
        gtk_ui_manager_insert_action_group (
                manager, GTK_ACTION_GROUP (object), 0);

        object = gtk_builder_get_object (builder, "lockable-actions");
        gtk_ui_manager_insert_action_group (
                manager, GTK_ACTION_GROUP (object), 0);
}
