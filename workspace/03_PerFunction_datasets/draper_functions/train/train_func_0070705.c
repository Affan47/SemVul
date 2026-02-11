line_width_changed_cb (GtkSpinButton        *spin,
		       glUIPropertyBar      *this)
{
	gdouble line_width;

	if (this->priv->stop_signals) return;
	this->priv->stop_signals = TRUE;

	gl_debug (DEBUG_PROPERTY_BAR, "START");

	if (this->priv->label)
        {
		line_width = gtk_spin_button_get_value (spin);

		gl_label_set_selection_line_width (this->priv->label,
                                                   line_width);
		gl_label_set_default_line_width   (this->priv->label,
                                                   line_width);
	}

	gl_debug (DEBUG_PROPERTY_BAR, "END");

	this->priv->stop_signals = FALSE;
}
