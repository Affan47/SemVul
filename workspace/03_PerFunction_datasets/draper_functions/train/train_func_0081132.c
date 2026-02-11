ario_plugin_manager_init (ArioPluginManager *pm)
{
        GtkWidget *label;
        GtkWidget *alignment;
        GtkWidget *viewport;
        GtkWidget *hbuttonbox;
        gchar *markup;

        pm->priv = ARIO_PLUGIN_MANAGER_GET_PRIVATE (pm);

        gtk_box_set_spacing (GTK_BOX (pm), 6);

        label = gtk_label_new (NULL);
        markup = g_markup_printf_escaped ("<span weight=\"bold\">%s</span>",
                                          _("Active plugins"));
        gtk_label_set_markup (GTK_LABEL (label), markup);
        g_free (markup);
        gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);

        gtk_box_pack_start (GTK_BOX (pm), label, FALSE, TRUE, 0);

        alignment = gtk_alignment_new (0., 0., 1., 1.);
        gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 0, 12, 0);
        gtk_box_pack_start (GTK_BOX (pm), alignment, TRUE, TRUE, 0);

        viewport = gtk_scrolled_window_new (NULL, NULL);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (viewport),
                                        GTK_POLICY_AUTOMATIC,
                                        GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (viewport),
                                             GTK_SHADOW_IN);

        gtk_container_add (GTK_CONTAINER (alignment), viewport);

        pm->priv->tree = gtk_tree_view_new ();
        gtk_container_add (GTK_CONTAINER (viewport), pm->priv->tree);

        hbuttonbox = gtk_hbutton_box_new ();
        gtk_box_pack_start (GTK_BOX (pm), hbuttonbox, FALSE, FALSE, 0);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox), GTK_BUTTONBOX_END);
        gtk_box_set_spacing (GTK_BOX (hbuttonbox), 8);

        pm->priv->about_button = gtk_button_new_from_stock (GTK_STOCK_ABOUT);
        gtk_container_add (GTK_CONTAINER (hbuttonbox), pm->priv->about_button);

        pm->priv->configure_button = gtk_button_new_from_stock (GTK_STOCK_PREFERENCES);
        gtk_container_add (GTK_CONTAINER (hbuttonbox), pm->priv->configure_button);


        gtk_widget_set_size_request (GTK_WIDGET (viewport), 270, 100);

        g_signal_connect (pm->priv->about_button,
                          "clicked",
                          G_CALLBACK (about_button_cb),
                          pm);
        g_signal_connect (pm->priv->configure_button,
                          "clicked",
                          G_CALLBACK (configure_button_cb),
                          pm);

        plugin_manager_construct_tree (pm);

        if (ario_plugins_engine_get_plugin_list () != NULL) {
                plugin_manager_populate_lists (pm);
        } else {
                gtk_widget_set_sensitive (pm->priv->about_button, FALSE);
                gtk_widget_set_sensitive (pm->priv->configure_button, FALSE);
        }
}
