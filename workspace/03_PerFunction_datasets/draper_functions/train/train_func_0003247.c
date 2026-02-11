upnp_msearch_reply(const gnutella_socket_t *s,
	const void *data, size_t len, bool truncated)
{
	int code;
	header_t *header;
	char *location;
	char *st;
	struct upnp_mcb *mcb;
	struct upnp_dscv *udev;
	GSList *sl;


	mcb = htable_lookup(pending, s);

	if (NULL == mcb) {
		g_warning("unexpected UPnP reply from %s",
			host_addr_to_string(s->addr));
		return;
	}

	mcb->replies++;


	if (GNET_PROPERTY(upnp_debug) > 5) {
		g_debug("UPNP %sM-SEARCH reply from %s",
			truncated ? "truncated " : "", host_addr_to_string(s->addr));
	}

	if (GNET_PROPERTY(http_trace) & SOCK_TRACE_IN) {
		g_debug("----Got HTTP reply (UDP) from %s (%zu bytes):",
			host_addr_to_string(s->addr), len);
		dump_string(stderr, data, len, "----");
	}


	header = http_header_parse(data, len, &code, NULL, NULL, NULL, NULL);

	if (NULL == header)
		return;

	if (code != 200)
		goto done;


	if (NULL == header_get(header, "Ext"))
		goto done;

	location = header_get(header, "Location");
	st = header_get(header, "ST");

	if (NULL == location || NULL == st)
		goto done;


	if (GNET_PROPERTY(upnp_debug) > 5) {
		g_debug("UPNP M-SEARCH found \"%s\" at %s", st, location);
	}

	mcb->valid++;


	GM_SLIST_FOREACH(mcb->devices, sl) {
		struct upnp_dscv *ud = sl->data;

		if (0 == strcmp(location, ud->desc_url))
			goto done;
	}


	if (GNET_PROPERTY(upnp_debug) > 1) {
		g_message("UPNP M-SEARCH discovered device %s", location);
	}


	{
		struct upnp_dscv_context *dctx;
		struct http_async *ha;

		WALLOC0(udev);
		udev->magic = UPNP_DSCV_MAGIC;
		udev->desc_url = atom_str_get(location);

		WALLOC0(dctx);
		dctx->mcb = mcb;
		dctx->ud = udev;

		ha = http_async_wget(location, UPNP_XML_MAXLEN, upnp_dscv_probed, dctx);

		if (NULL == ha) {
			g_warning("UPNP cannot probe \"%s\": %s",
				location, http_async_strerror(http_async_errno));
			WFREE(dctx);
			upnp_dscv_free(udev);
			goto done;
		}

		udev->ha = ha;
	}


	mcb->devices = g_slist_prepend(mcb->devices, udev);
	mcb->pending_probes++;

done:
	header_free(header);
}
