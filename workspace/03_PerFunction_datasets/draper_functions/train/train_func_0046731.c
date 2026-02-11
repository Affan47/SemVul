rb_player_gst_xfade_dispose (GObject *object)
{
	RBPlayerGstXFade *player;
	GList *l;

	g_return_if_fail (RB_IS_PLAYER_GST_XFADE (object));
	player = RB_PLAYER_GST_XFADE (object);


	g_rec_mutex_lock (&player->priv->stream_list_lock);
	for (l = player->priv->streams; l != NULL; l = l->next) {
		RBXFadeStream *stream = (RBXFadeStream *)l->data;


		gst_element_set_state (GST_ELEMENT (stream), GST_STATE_NULL);

		g_object_unref (stream);
	}
	g_list_free (player->priv->streams);
	player->priv->streams = NULL;
	g_rec_mutex_unlock (&player->priv->stream_list_lock);

	if (player->priv->volume_handler) {
		g_object_unref (player->priv->volume_handler);
		player->priv->volume_handler = NULL;
	}

	g_rec_mutex_lock (&player->priv->sink_lock);
	stop_sink (player);
	g_rec_mutex_unlock (&player->priv->sink_lock);

	if (player->priv->pipeline != NULL) {

		gst_element_set_state (player->priv->pipeline, GST_STATE_NULL);
		g_object_unref (player->priv->pipeline);
		player->priv->pipeline = NULL;
	}

	G_OBJECT_CLASS (rb_player_gst_xfade_parent_class)->dispose (object);
}
