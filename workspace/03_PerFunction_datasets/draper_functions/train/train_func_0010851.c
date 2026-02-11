inv_knob_realize(GtkWidget *widget)
{
	GdkWindowAttr attributes;
	guint attributes_mask;

	g_return_if_fail(widget != NULL);
	g_return_if_fail(INV_IS_KNOB(widget));

	GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);

	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.x = widget->allocation.x;
	attributes.y = widget->allocation.y;
	attributes.width = INV_KNOB (widget)->size + 4;
	switch(INV_KNOB (widget)->size) {
		case INV_KNOB_SIZE_SMALL:
			attributes.height = INV_KNOB (widget)->size + 50;
			break;
		case INV_KNOB_SIZE_MEDIUM:
			attributes.height = INV_KNOB (widget)->size + 56;
			break;
		case INV_KNOB_SIZE_LARGE:
		default:
			attributes.height = INV_KNOB (widget)->size + 62;
			break;
	}


	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.event_mask = gtk_widget_get_events(widget) |
				GDK_EXPOSURE_MASK |
				GDK_BUTTON_PRESS_MASK |
				GDK_BUTTON_RELEASE_MASK |
				GDK_BUTTON_MOTION_MASK;

	attributes_mask = GDK_WA_X | GDK_WA_Y;

	widget->window = gdk_window_new(
	  gtk_widget_get_parent_window (widget),
	  & attributes, attributes_mask
	);

	gdk_window_set_user_data(widget->window, widget);

	widget->style = gtk_style_attach(widget->style, widget->window);
	gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);
}
