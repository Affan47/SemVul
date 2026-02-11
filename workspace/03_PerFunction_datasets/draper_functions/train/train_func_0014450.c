download_push_proxy_wakeup(struct dl_server *server,
	bool udp, bool broadcast)
{
	list_iter_t *iter;
	uint32 n = GNET_PROPERTY(max_host_downloads);
	time_t now;
	uint sent = 0;


	iter = list_iter_before_head(server->list[DL_LIST_RUNNING]);
	while (list_iter_has_next(iter) && n != 0) {
		struct download *d = list_iter_next(iter);
		download_check(d);
		if (udp)
			d->flags &= ~DL_F_UDP_PUSH;
		if (DOWNLOAD_IS_EXPECTING_GIV(d)) {
			if (download_send_push_request(d, udp, broadcast)) {
				n--;
				sent++;
			}
		}
	}
	list_iter_free(&iter);


	if (n == 0)
		goto done;

	if (GNET_PROPERTY(max_host_downloads) <= count_running_on_server(server))
		goto done;

	n = GNET_PROPERTY(max_host_downloads) - count_running_on_server(server);
	now = tm_time();

	iter = list_iter_before_head(server->list[DL_LIST_WAITING]);
	while (list_iter_has_next(iter) && n != 0) {
		struct download *d = list_iter_next(iter);
		download_check(d);
		d->flags &= ~DL_F_UDP_PUSH;
		if (d->flags & (DL_F_SUSPENDED | DL_F_PAUSED))
			continue;
		if (
			GTA_DL_TIMEOUT_WAIT == d->status ||
			delta_time(now, d->retry_after) >= 0
		) {
			if (download_send_push_request(d, udp, broadcast)) {
				n--;
				sent++;
			}
		}
	}
	list_iter_free(&iter);

done:
	if (GNET_PROPERTY(download_debug) > 1) {
		g_debug("PUSH %s %u message%s on wakeup for GUID %s at %s",
			broadcast ? "broadcasted" : "sent",
			sent, 1 == sent ? "" : "s",
			guid_hex_str(server->key->guid), server_host_info(server));
	}
}
