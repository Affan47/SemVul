gedit_panel_constructed (GObject *object)
{
	GeditPanel *panel = GEDIT_PANEL (object);
	GtkStyleContext *context;


	context = gtk_widget_get_style_context (GTK_WIDGET (panel));

	build_notebook_for_panel (panel);
	if (panel->priv->orientation == GTK_ORIENTATION_HORIZONTAL)
	{
		build_horizontal_panel (panel);
		gtk_style_context_add_class (context, GTK_STYLE_CLASS_HORIZONTAL);
	}
	else
	{
		build_vertical_panel (panel);
		gtk_style_context_add_class (context, GTK_STYLE_CLASS_VERTICAL);
	}

	g_signal_connect (panel,
			  "show",
			  G_CALLBACK (panel_show),
			  NULL);

	G_OBJECT_CLASS (gedit_panel_parent_class)->constructed (object);
}
