glade_fixed_handle_swindow (GladeFixed   *fixed,
			    GdkRectangle *area)
{
	GtkWidget     *fixed_widget = GTK_WIDGET (GLADE_WIDGET (fixed)->object);
	GtkWidget     *swindow = NULL, *swindow_child = NULL;
	GtkAdjustment *hadj, *vadj;
	GtkAllocation  child_allocation;
	gint           x, y;

	swindow_child = swindow = fixed_widget;
	while (swindow && !GTK_IS_SCROLLED_WINDOW (swindow))
	{
		if (!GTK_IS_VIEWPORT (swindow))
			swindow_child = swindow;

		swindow = gtk_widget_get_parent (swindow);
	}

	if (swindow)
	{


		hadj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (swindow));
		vadj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (swindow));
		gtk_widget_get_allocation (swindow_child, &child_allocation);

		g_object_set (G_OBJECT (hadj),
			      "lower", 0.0F,
			      "upper", (gdouble) child_allocation.width + 0.0,
			      NULL);

		g_object_set (G_OBJECT (vadj),
			      "lower", 0.0F,
			      "upper", (gdouble) child_allocation.height + 0.0,
			      NULL);

		gtk_widget_translate_coordinates (fixed_widget,
						  swindow_child,
						  area->x, area->y, &x, &y);

		gtk_adjustment_clamp_page (hadj, x, x + area->width);
		gtk_adjustment_clamp_page (vadj, y, y + area->height);
	}
}
