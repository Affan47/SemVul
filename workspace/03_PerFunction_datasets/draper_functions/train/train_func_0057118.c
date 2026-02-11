magnet_source_to_string(const struct magnet_source *s)
{
	char *url;

	g_return_val_if_fail(s, NULL);

	if (s->url) {
		url = g_strdup(s->url);
	} else {
		char *proxies = NULL;
		const char *host, *prefix;
		char prefix_buf[256];
		char port_buf[16];

		if (s->guid) {
			char guid_buf[GUID_HEX_SIZE + 1];

			guid_to_string_buf(s->guid, guid_buf, sizeof guid_buf);
			concat_strings(prefix_buf, sizeof prefix_buf,
				"push://", guid_buf, (void *) 0);
			prefix = prefix_buf;
		} else {
			prefix = "http://";
		}

		port_buf[0] = '\0';
		if (s->hostname) {
			host = s->hostname;
			if (80 != s->port) {
				str_bprintf(port_buf, sizeof port_buf, ":%u",
					(unsigned) s->port);
			}
		} else if (s->guid) {
			proxies = proxies_to_string(s->proxies);
			host = proxies;
		} else {
			host = host_addr_port_to_string(s->addr, s->port);
		}
		if (s->path) {
			url = g_strconcat(prefix, host, port_buf, s->path, (void *) 0);
		} else if (s->sha1) {
			url = g_strconcat(prefix, host, port_buf,
					"/uri-res/N2R?", bitprint_to_urn_string(s->sha1, s->tth),
					(void *) 0);
		} else {
			url = g_strconcat(prefix, host, port_buf, "/", (void *) 0);
		}

		HFREE_NULL(proxies);
	}

	return url;
}
