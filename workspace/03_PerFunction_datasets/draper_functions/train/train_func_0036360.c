cg_window_add_project_toggled_cb (GtkToggleButton *button,
                                  gpointer user_data)
{
	CgWindow *window;
	CgWindowPrivate *priv;
	GtkWidget *widget;
	gboolean sensitive;

	window = CG_WINDOW (user_data);
	priv = CG_WINDOW_PRIVATE (window);

	sensitive = gtk_toggle_button_get_active (button);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->bxml, "add_repository"));
	gtk_widget_set_sensitive (widget, sensitive);
	if (!sensitive)
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget),
		                              FALSE);
	}
	widget = GTK_WIDGET (gtk_builder_get_object (priv->bxml, "add_project_parent"));
	gtk_widget_set_sensitive (widget, sensitive);

	cg_window_add_project_parent_changed_cb (NULL, window);
}
