panel_menu_bar_object_init (PanelMenuBarObject *menubar)
{
        GtkStyleContext *context;
        GtkCssProvider *provider;

	menubar->priv = PANEL_MENU_BAR_OBJECT_GET_PRIVATE (menubar);

        provider = gtk_css_provider_new ();
        gtk_css_provider_load_from_data (provider,
                                         "PanelMenuBarObject {\n"
                                         " border-width: 0px;\n"
                                         "}",
                                         -1, NULL);
        context = gtk_widget_get_style_context (GTK_WIDGET (menubar));
        gtk_style_context_add_provider (context,
                                        GTK_STYLE_PROVIDER (provider),
                                        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        g_object_unref (provider);
	gtk_style_context_add_class (context, "gnome-panel-menu-bar");

	if (menubar->priv->orientation & PANEL_HORIZONTAL_MASK)
		gtk_style_context_add_class (context, GTK_STYLE_CLASS_HORIZONTAL);
	else
		gtk_style_context_add_class (context, GTK_STYLE_CLASS_VERTICAL);

	menubar->priv->panel = NULL;
}
