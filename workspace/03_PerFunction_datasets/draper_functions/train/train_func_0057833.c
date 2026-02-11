about_to_finish_cb (GstElement *playbin, RBPlayerGst *player)
{
	if (player->priv->stream_change_pending == TRUE) {

		rb_debug ("got about-to-finish, but we already have a stream change pending.");
		return;
	}


	if (g_str_has_prefix (player->priv->uri, "cdda://")) {
		rb_debug ("ignoring about-to-finish for %s", player->priv->uri);
		return;
	}

	player->priv->current_track_finishing = TRUE;

	g_mutex_lock (&player->priv->eos_lock);
	g_idle_add_full (G_PRIORITY_HIGH, (GSourceFunc) about_to_finish_idle, player, NULL);

	g_cond_wait (&player->priv->eos_cond, &player->priv->eos_lock);
	g_mutex_unlock (&player->priv->eos_lock);
}
