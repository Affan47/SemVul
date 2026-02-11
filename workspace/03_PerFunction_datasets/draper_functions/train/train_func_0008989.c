gth_grid_view_key_release (GtkWidget   *widget,
			   GdkEventKey *event)
{
	GthGridView *self = GTH_GRID_VIEW (widget);

	if (self->priv->multi_selecting_with_keyboard
	    && (event->state & GDK_SHIFT_MASK)
	    && ((event->keyval == GDK_KEY_Shift_L)
		|| (event->keyval == GDK_KEY_Shift_R)))
	{
		self->priv->multi_selecting_with_keyboard = FALSE;
	}

	gtk_widget_queue_draw (widget);

	if ((GTK_WIDGET_CLASS (gth_grid_view_parent_class)->key_press_event != NULL)
	    && GTK_WIDGET_CLASS (gth_grid_view_parent_class)->key_press_event (widget, event))
	{
		return TRUE;
	}

	return FALSE;
}
