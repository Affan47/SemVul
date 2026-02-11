bitmap_button_button_press ( GtkWidget *widget, GdkEventButton *event )
{
	if (event->type == GDK_BUTTON_PRESS && event->button == 1)
	{
		BitmapButton *self = BITMAP_BUTTON (widget);
		gdouble value = gtk_adjustment_get_value (self->adjustment);
		gdouble lower = gtk_adjustment_get_lower (self->adjustment);
		gdouble upper = gtk_adjustment_get_upper (self->adjustment);
		gdouble middl = (upper - lower) / 2.0;
		gtk_adjustment_set_value (self->adjustment, (value < middl) ? 1.0 : 0.0);
		return TRUE;
	}
	return FALSE;
}
