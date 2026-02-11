font_size_changed_cb (GtkSpinButton        *spin,
		      glUIPropertyBar      *this)
{
	gdouble font_size;

	if (this->priv->stop_signals) return;
	this->priv->stop_signals = TRUE;

	gl_debug (DEBUG_PROPERTY_BAR, "START");

	font_size = gtk_spin_button_get_value (spin);

	gl_label_set_selection_font_size (this->priv->label,
					  font_size);
	gl_label_set_default_font_size   (this->priv->label,
                                          font_size);

	gl_debug (DEBUG_PROPERTY_BAR, "END");

	this->priv->stop_signals = FALSE;
}
