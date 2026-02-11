bitzi_ticket_requested(char *data, size_t len, int code,
	header_t *header, void *arg)
{
	bitzi_request_t *breq = arg;
	const char *buf;

	breq->ha = NULL;

	if (NULL == data) {
		if (GNET_PROPERTY(bitzi_debug)) {
			g_warning("BITZI requested ticket for %s failed (HTTP %d)",
				sha1_to_string(breq->sha1), code);
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto done;
	}

	if (GNET_PROPERTY(bitzi_debug) > 1) {
		g_debug("BITZI request for %s returned %zu byte%s",
			sha1_to_string(breq->sha1),
			len, 1 == len ? "" : "s");
		if (GNET_PROPERTY(bitzi_debug) > 5) {
			g_debug("BITZI got HTTP %u:", code);
			header_dump(stderr, header, "----");
		}
		if (GNET_PROPERTY(bitzi_debug) > 9) {
			dump_hex(stderr, "BITZI ticket", data, len);
		}
	}


	buf = header_get(header, "Content-Type");
	if (NULL == buf || !strtok_case_has(buf, ";", "text/xml")) {
		g_warning("BITZI ticket for %s does not contain any XML",
			sha1_to_string(breq->sha1));
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto done;
	}


	bitzi_process_ticket(breq, data, len);
	hfree(data);


done:
	current_bitzi_request = NULL;
	bitzi_request_free(breq);
}
