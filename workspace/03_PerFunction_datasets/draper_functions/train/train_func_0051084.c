glade_widget_hide (GladeWidget *widget)
{
	g_return_if_fail (GLADE_IS_WIDGET (widget));
	if (GTK_IS_WIDGET (widget->object))
	{
		GladeDesignView *view;
		GtkWidget *layout;

		if ((view = glade_design_view_get_from_project (glade_widget_get_project (widget))) != NULL)
		{
			GtkWidget *child;

			layout = GTK_WIDGET (glade_design_view_get_layout (view));
			child = gtk_bin_get_child (GTK_BIN (layout));

			if (child == GTK_WIDGET (widget->object))
				gtk_container_remove (GTK_CONTAINER (layout), child);
		}

		gtk_widget_hide (GTK_WIDGET (widget->object));
	}
	widget->visible = FALSE;
}
