font_family_changed_cb (GtkComboBox     *combo,
			glUIPropertyBar *this)
{
	gchar *font_family;

	if (this->priv->stop_signals) return;
	this->priv->stop_signals = TRUE;

	gl_debug (DEBUG_PROPERTY_BAR, "START");

	font_family = gl_font_combo_get_family (GL_FONT_COMBO (combo));
	if ( *font_family != '\0' )
        {
                gl_label_set_selection_font_family (this->priv->label, font_family);
                gl_label_set_default_font_family   (this->priv->label, font_family);
        }
        g_free (font_family);

	gl_debug (DEBUG_PROPERTY_BAR, "END");

	this->priv->stop_signals = FALSE;
}
