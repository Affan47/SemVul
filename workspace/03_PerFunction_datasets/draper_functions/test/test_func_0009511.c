http_timer(time_t now)
{
	GSList *l;

retry:
	for (l = sl_outgoing; l; l = l->next) {
		http_async_t *ha = l->data;
		int elapsed = delta_time(now, ha->last_update);
		int timeout = ha->rx
			? GNET_PROPERTY(download_connected_timeout)
			: GNET_PROPERTY(download_connecting_timeout);

		if (ha->flags & HA_F_SUBREQ)
			continue;

		if (elapsed > timeout) {
			switch (ha->state) {
			case HTTP_AS_UNKNOWN:
			case HTTP_AS_CONNECTING:
				http_async_error(ha, HTTP_ASYNC_CONN_TIMEOUT);
				goto retry;
			case HTTP_AS_REMOVED:
				g_error("removed async request should not be listed");
				break;
			default:
				http_async_error(ha, HTTP_ASYNC_TIMEOUT);
				goto retry;
			}
		}
	}


	if (sl_ha_freed)
		http_async_free_pending();
}
