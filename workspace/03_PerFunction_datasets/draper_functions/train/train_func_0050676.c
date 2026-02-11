autoscroll_cb (gpointer user_data)
{
	GthGridView *self = user_data;
	double       max_value;
	double       value;

	max_value = gtk_adjustment_get_upper (self->priv->vadjustment) - gtk_adjustment_get_page_size (self->priv->vadjustment);
	value = gtk_adjustment_get_value (self->priv->vadjustment) + self->priv->autoscroll_y_delta;
	if (value > max_value)
		value = max_value;

	gtk_adjustment_set_value (self->priv->vadjustment, value);
	self->priv->event_last_y = self->priv->event_last_y + self->priv->autoscroll_y_delta;
	_gth_grid_view_update_mouse_selection (self, self->priv->event_last_x, self->priv->event_last_y);

	return TRUE;
}
