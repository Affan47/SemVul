bitzi_process_ticket(bitzi_request_t *breq, char *ticket, size_t length)
{
	bitzi_data_t *data;
	xnode_t *root;
	vxml_parser_t *vp;
	vxml_error_t e;

	g_assert(breq != NULL);

	if (GNET_PROPERTY(bitzi_debug)) {
		g_debug("BITZI %s: processing ticket data for %s",
			G_STRFUNC, sha1_to_string(breq->sha1));
	}


	vp = vxml_parser_make("BITZI ticket", VXML_O_STRIP_BLANKS);
	vxml_parser_add_data(vp, ticket, length);
	e = vxml_parse_tree(vp, &root);
	vxml_parser_free(vp);

	if (VXML_E_OK != e) {
		if (GNET_PROPERTY(bitzi_debug)) {
			g_warning("BITZI cannot parse XML ticket: %s", vxml_strerror(e));
			dump_hex(stderr, "BITZI ticket", ticket, length);
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		return;
	}


   	data = bitzi_create();


	bitzi_process_xml(root, data);

	if (NULL == data->sha1) {
		if (GNET_PROPERTY(bitzi_debug))  {
			g_warning("process_meta_data: missing SHA-1");
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto finish;
	}

	if (breq->sha1 && !sha1_eq(data->sha1, breq->sha1)) {
		if (GNET_PROPERTY(bitzi_debug))  {
			g_warning("process_meta_data: SHA-1 mismatch");
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto finish;
	}


	if (
		(time_t) -1 == data->expiry ||
		delta_time(data->expiry, tm_time()) <= 0
	) {
		if (GNET_PROPERTY(bitzi_debug))  {
			g_debug("BITZI %s: stale bitzi data", G_STRFUNC);
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto finish;
	}

	if (!bitzi_cache_add(data, root)) {
		if (GNET_PROPERTY(bitzi_debug))  {
			g_debug("BITZI %s: uncached bitzi data", G_STRFUNC);
		}
		bitzi_failure(breq->sha1, breq->filesize, BITZI_FJ_FAILURE);
		goto finish;
	}

	if (breq->filesize && breq->filesize != data->size) {
		if (GNET_PROPERTY(bitzi_debug))  {
			g_debug("BITZI %s: filesize mismatch", G_STRFUNC);
		}

		bitzi_failure(breq->sha1, breq->filesize,
			data->size ? BITZI_FJ_WRONG_FILESIZE : BITZI_FJ_UNKNOWN);
		goto finish;
	}

	gcu_bitzi_result(data);


finish:
	xnode_tree_free_null(&root);
	bitzi_destroy(data);
}
