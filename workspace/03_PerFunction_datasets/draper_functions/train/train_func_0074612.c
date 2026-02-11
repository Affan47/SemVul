brasero_song_control_range_button_released_cb (GtkWidget *widget,
                                               GdkEvent *event,
                                               BraseroSongControl *player)
{
	BraseroSongControlPrivate *priv;

	priv = BRASERO_SONG_CONTROL_PRIVATE (player);


	if (priv->state == GST_STATE_PLAYING && !priv->update_scale_id)
		priv->update_scale_id = g_timeout_add (500,
		                                       (GSourceFunc) brasero_song_control_update_progress_cb,
		                                       player);

	return FALSE;
}
