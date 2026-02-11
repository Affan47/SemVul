gth_image_viewer_scroll_event (GtkWidget      *widget,
			       GdkEventScroll *event)
{
	GthImageViewer *self = GTH_IMAGE_VIEWER (widget);
	gdouble         new_value = 0.0;
	gboolean        retval = FALSE;

	g_return_val_if_fail (GTH_IS_IMAGE_VIEWER (widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);


	if (event->state & GDK_CONTROL_MASK) {
		if  (self->priv->zoom_enabled) {
			double new_zoom_level;

			switch (event->direction) {
			case GDK_SCROLL_UP:
			case GDK_SCROLL_DOWN:
				if (event->direction == GDK_SCROLL_UP)
					new_zoom_level = get_next_zoom (self->priv->zoom_level);
				else
					new_zoom_level = get_prev_zoom (self->priv->zoom_level);
				set_zoom_centered_at (self, new_zoom_level, FALSE, (int) event->x, (int) event->y);
				gtk_widget_queue_resize (GTK_WIDGET (self));
				retval = TRUE;
				break;

			default:
				break;
			}
		}

		return retval;
	}


	switch (event->direction) {
	case GDK_SCROLL_LEFT:
	case GDK_SCROLL_RIGHT:
		if (event->direction == GDK_SCROLL_LEFT)
			new_value = gtk_adjustment_get_value (self->hadj) - gtk_adjustment_get_page_increment (self->hadj) / 2;
		else
			new_value = gtk_adjustment_get_value (self->hadj) + gtk_adjustment_get_page_increment (self->hadj) / 2;
		new_value = CLAMP (new_value, gtk_adjustment_get_lower (self->hadj), gtk_adjustment_get_upper (self->hadj) - gtk_adjustment_get_page_size (self->hadj));
		gtk_adjustment_set_value (self->hadj, new_value);
		retval = TRUE;
		break;

	default:
		break;
	}

	return retval;
}
