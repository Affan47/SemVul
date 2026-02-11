back_channel_main(void *arg)
{
	struct peer *peer0 = arg, *peer;
	struct host *host = peer_get_host(peer0);;
	gfp_xdr_async_peer_t async;
	gfarm_error_t e;

	e = host_receiver_lock(host, &peer);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_error(GFARM_MSG_1002327,
		    "back_channel(%s): aborted: %s",
		    host_name(host), gfarm_error_string(e));
		sync_back_channel_free(host);
		peer_invoked(peer0);
		return (NULL);
	}


	if (peer != peer0) {
		gflog_error(GFARM_MSG_1002328,
		    "back_channel(%s): aborted: unexpected peer switch",
		    host_name(host));
		sync_back_channel_free(host);
		host_receiver_unlock(host, peer);
		peer_invoked(peer0);
		return (NULL);
	}


	peer_invoked(peer);

	async = peer_get_async(peer);

	do {
		if (peer_had_protocol_error(peer)) {

			sync_back_channel_free(host);
			host_receiver_unlock(host, peer);
			gflog_debug(GFARM_MSG_1002439,
			    "back_channel(%s): host_disconnect was called",
			    host_name(host));
			return (NULL);
		}
#ifdef COMPAT_GFARM_2_3
		if (async != NULL) {
#endif
			e = async_back_channel_service(host, peer, async);
#ifdef COMPAT_GFARM_2_3
		} else {
			e = sync_back_channel_service(host, peer);
		}
#endif
		if (IS_CONNECTION_ERROR(e)) {
			if (e == GFARM_ERR_UNEXPECTED_EOF) {
				gflog_error(GFARM_MSG_1002286,
				    "back_channel(%s): disconnected",
				    host_name(host));
			} else {
				gflog_error(GFARM_MSG_1002287,
				    "back_channel(%s): "
				    "request error, reset: %s",
				     host_name(host), gfarm_error_string(e));
			}
			sync_back_channel_free(host);
			host_disconnect_request(host, peer);
			host_receiver_unlock(host, peer);
			return (NULL);
		}
	} while (gfp_xdr_recv_is_ready(peer_get_conn(peer)));


	peer_watch_access(peer);

	host_receiver_unlock(host, peer);


	return (NULL);
}
