background_transparent_toggled_cb (GtkToggleButton   *toggle_button,
		             	   GthFileToolRotate *self)
{
	if (gtk_toggle_button_get_active (toggle_button)) {
		GdkRGBA background_color;

		background_color.red = 0.0;
		background_color.green = 0.0;
		background_color.blue = 0.0;
		background_color.alpha = 0.0;
		gth_image_rotator_set_background (GTH_IMAGE_ROTATOR (self->priv->rotator), &background_color);
	}
	else
		background_colorbutton_color_set_cb (GTK_COLOR_BUTTON (GET_WIDGET ("background_colorbutton")), self);
}
