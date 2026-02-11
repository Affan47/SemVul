cb_image_style_changed (GtkWidget *w, StylePrefState *state)
{
	GOStyle *style = state->style;
	g_return_if_fail (style != NULL);
	g_return_if_fail (GO_STYLE_FILL_IMAGE == style->fill.type);
	style->fill.image.type = gtk_combo_box_get_active (GTK_COMBO_BOX (w));
	set_style (state);
}
