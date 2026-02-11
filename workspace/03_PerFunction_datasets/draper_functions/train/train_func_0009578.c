rb_ipod_db_queue_remove_playlist (RbIpodDb *ipod_db,
				  Itdb_Playlist *playlist)
{
	RbIpodDelayedAction *action;
	RbIpodDbPrivate *priv = IPOD_DB_GET_PRIVATE (ipod_db);

	g_assert (priv->read_only);
	rb_debug ("Queueing remove playlist action since the iPod database is currently read-only");
	action = g_new0 (RbIpodDelayedAction, 1);
	action->type = RB_IPOD_ACTION_REMOVE_PLAYLIST;
	action->playlist_op.playlist = playlist;
	g_queue_push_tail (priv->delayed_actions, action);
}
