brasero_audio_disc_key_released_cb (GtkTreeView *tree,
				    GdkEventKey *event,
				    BraseroAudioDisc *disc)
{
	if (disc->priv->editing)
		return FALSE;

	if (event->keyval == GDK_KEY_KP_Delete || event->keyval == GDK_KEY_Delete) {
		brasero_audio_disc_delete_selected (BRASERO_DISC (disc));
	}
	else if (event->keyval == GDK_KEY_F2)
		brasero_audio_disc_rename_activated (disc);

	return FALSE;
}
