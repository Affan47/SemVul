prune_peers(void)
{
	struct iax2_peer *peer;
	struct ao2_iterator i;

	i = ao2_iterator_init(peers, 0);
	while ((peer = ao2_iterator_next(&i))) {
		if (ast_test_flag64(peer, IAX_DELME) || ast_test_flag64(peer, IAX_RTCACHEFRIENDS)) {
			unlink_peer(peer);
		}
		peer_unref(peer);
	}
	ao2_iterator_destroy(&i);
}
