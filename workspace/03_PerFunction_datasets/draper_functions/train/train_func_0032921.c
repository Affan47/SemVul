peer_del_ref(struct peer *peer)
{
	int referenced;
	static const char diag[] = "peer_del_ref";

	gfarm_mutex_lock(&peer_closing_queue.mutex,
	    diag, "peer_closing_queue");

	if (--peer->refcount > 0) {
		referenced = 1;
	} else {
		referenced = 0;
		gfarm_cond_signal(&peer_closing_queue.ready_to_close,
		    diag, "ready to close");
	}

	gfarm_mutex_unlock(&peer_closing_queue.mutex,
	    diag, "peer_closing_queue");

	return (referenced);
}
