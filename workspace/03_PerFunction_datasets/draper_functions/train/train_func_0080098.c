gbemol_app_set_volume (GbemolApp* app, gint volume)
{
	if ((volume >= 0) && (volume <= 100))
		bacon_volume_button_set_value (BACON_VOLUME_BUTTON (app->priv->btn_volume), (float) volume);
}
