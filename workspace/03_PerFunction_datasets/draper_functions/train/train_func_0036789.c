plugin_dialog_init (PluginDialog *pm)
{
	GtkWidget *label;
	GtkWidget *viewport;
	GtkWidget *hbuttonbox;

	gphpedit_debug(DEBUG_PLUGINS);

	pm->priv = PLUGIN_DIALOG_GET_PRIVATE (pm);

	gtk_box_set_spacing (GTK_BOX (pm), 6);

	label = gtk_label_new_with_mnemonic (_("Active _Plugins:"));
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
	gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);

	gtk_box_pack_start (GTK_BOX (pm), label, FALSE, TRUE, 0);

	viewport = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (viewport),
					GTK_POLICY_AUTOMATIC,
					GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (viewport),
					     GTK_SHADOW_IN);

	gtk_box_pack_start (GTK_BOX (pm), viewport, TRUE, TRUE, 0);

	pm->priv->tree = gtk_tree_view_new ();
	gtk_container_add (GTK_CONTAINER (viewport), pm->priv->tree);

	gtk_label_set_mnemonic_widget (GTK_LABEL (label), pm->priv->tree);

	hbuttonbox = gtk_hbutton_box_new ();
	gtk_box_pack_start (GTK_BOX (pm), hbuttonbox, FALSE, FALSE, 0);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox), GTK_BUTTONBOX_END);
	gtk_box_set_spacing (GTK_BOX (hbuttonbox), 8);

	pm->priv->about_button = gphpedit_gtk_button_new_with_stock_icon (_("_About Plugin"),
								       GTK_STOCK_ABOUT);
	gtk_container_add (GTK_CONTAINER (hbuttonbox), pm->priv->about_button);


	gtk_widget_set_size_request (GTK_WIDGET (viewport), 270, 100);

	g_signal_connect (pm->priv->about_button,
			  "clicked",
			  G_CALLBACK (about_button_cb),
			  pm);

	plugin_dialog_construct_tree (pm);


	pm->priv->engine = plugin_manager_new ();

	if (get_plugin_manager_items (pm->priv->engine) != NULL)
	{
		plugin_dialog_populate_lists (pm);
	}
	else
	{
		gtk_widget_set_sensitive (pm->priv->about_button, FALSE);
	}
}
