lookup_host(ne_session *sess, struct host_info *info)
{
    if (sess->addrlist) return NE_OK;

    NE_DEBUG(NE_DBG_HTTP, "Doing DNS lookup on %s...\n", info->hostname);
    if (sess->notify_cb)
	sess->notify_cb(sess->notify_ud, ne_conn_namelookup, info->hostname);
    info->address = ne_addr_resolve(info->hostname, 0);
    if (ne_addr_result(info->address)) {
	char buf[256];
	ne_set_error(sess, _("Could not resolve hostname `%s': %s"),
		     info->hostname,
		     ne_addr_error(info->address, buf, sizeof buf));
	ne_addr_destroy(info->address);
	info->address = NULL;
	return NE_LOOKUP;
    } else {
	return NE_OK;
    }
}
