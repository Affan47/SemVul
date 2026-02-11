gth_time_selector_show_time (GthTimeSelector *self,
			     gboolean         show,
			     gboolean         optional)
{
	self->priv->use_time = show;
	self->priv->optional_time = optional;

	if (show || optional) {
		gtk_widget_show (self->priv->time_combo_box);
		gtk_widget_show (self->priv->now_button);
	}
	else {
		gtk_entry_set_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (self->priv->time_combo_box))), "00:00:00");
		gtk_widget_hide (self->priv->time_combo_box);
		gtk_widget_hide (self->priv->now_button);
	}

	if (self->priv->optional_time)
		gtk_widget_show (self->priv->use_time_checkbutton);
	else
		gtk_widget_hide (self->priv->use_time_checkbutton);

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->priv->use_time_checkbutton), self->priv->use_time);
	gtk_widget_set_sensitive (self->priv->time_combo_box, self->priv->use_time);
}
