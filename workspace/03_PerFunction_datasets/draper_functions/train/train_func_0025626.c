peer_init(int max_peers,
	struct thread_pool *thrpool, void *(*protocol_handler)(void *))
{
	int i;
	struct peer *peer;
	gfarm_error_t e;

	GFARM_MALLOC_ARRAY(peer_table, max_peers);
	if (peer_table == NULL)
		gflog_fatal(GFARM_MSG_1000278,
		    "peer table: %s", strerror(ENOMEM));
	peer_table_size = max_peers;

	for (i = 0; i < peer_table_size; i++) {
		peer = &peer_table[i];
		peer->next_close = NULL;
		peer->refcount = 0;
		peer->conn = NULL;
		peer->async = NULL;
		peer->username = NULL;
		peer->hostname = NULL;
		peer->user = NULL;
		peer->host = NULL;
		peer->process = NULL;
		peer->protocol_error = 0;

		peer->control = 0;
		gfarm_mutex_init(&peer->control_mutex,
		    "peer_init", "peer:control_mutex");

		peer->fd_current = -1;
		peer->fd_saved = -1;
		peer->flags = 0;
		peer->findxmlattrctx = NULL;
		peer->pending_new_generation = NULL;
		peer->u.client.jobs = NULL;

		gfarm_mutex_init(&peer->replication_mutex,
		    "peer_init", "replication");
		peer->simultaneous_replication_receivers = 0;

		peer->replicating_inodes.prev_inode =
		peer->replicating_inodes.next_inode =
		    &peer->replicating_inodes;
	}

#ifdef HAVE_EPOLL
	peer_epoll.fd = epoll_create(max_peers);
	if (peer_epoll.fd == -1)
		gflog_fatal(GFARM_MSG_1000279,
		    "epoll_create: %s\n", strerror(errno));
	GFARM_MALLOC_ARRAY(peer_epoll.events, max_peers);
	if (peer_epoll.events == NULL)
		gflog_fatal(GFARM_MSG_1000280,
		    "peer epoll event table: %s", strerror(ENOMEM));
	peer_epoll.nevents = max_peers;
#else
	GFARM_MALLOC_ARRAY(peer_poll_fds, max_peers);
	if (peer_poll_fds == NULL)
		gflog_fatal(GFARM_MSG_1000281,
		    "peer pollfd table: %s", strerror(ENOMEM));
#endif
	peer_default_protocol_handler = protocol_handler;
	peer_default_thread_pool = thrpool;
	e = create_detached_thread(peer_watcher, NULL);
	if (e != GFARM_ERR_NO_ERROR)
		gflog_fatal(GFARM_MSG_1000282,
		    "create_detached_thread(peer_watcher): %s",
			    gfarm_error_string(e));

	e = create_detached_thread(peer_closer, NULL);
	if (e != GFARM_ERR_NO_ERROR)
		gflog_fatal(GFARM_MSG_1000282,
		    "create_detached_thread(peer_closer): %s",
			    gfarm_error_string(e));
}
