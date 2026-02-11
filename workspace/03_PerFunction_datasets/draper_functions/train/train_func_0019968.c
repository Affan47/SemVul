get_file_to_upload_from_urn(struct upload *u, const header_t *header,
	const char *uri)
{
	struct tth tth_buf, *tth = NULL;
	struct sha1 sha1;
	shared_file_t *sf;

	upload_check(u);
	g_assert(NULL == u->sf);

	if (!uri)
		goto malformed;

	u->n2r = TRUE;

	if (urn_get_bitprint(uri, strlen(uri), &sha1, &tth_buf)) {
		tth = &tth_buf;
	} else if (urn_get_sha1(uri, &sha1)) {
		tth = NULL;
	} else {
		goto malformed;
	}

	if (spam_sha1_check(&sha1))
		goto not_found;

	upload_collect_locations(u, &sha1, header);


	sf = shared_file_by_sha1(&sha1);

	if (sf == NULL || sf == SHARE_REBUILDING) {
		const char *filename;

		filename = ignore_sha1_filename(&sha1);
 		atom_str_change(&u->name, filename ? filename : uri);
	} else {
 		atom_str_change(&u->name, shared_file_name_nfc(sf));
	}

	if (sf == SHARE_REBUILDING) {

		upload_error_remove(u, 503, N_("Library being rebuilt"));
		return -1;
	}

	if (sf == NULL) {
		upload_error_not_found(u, uri);
		return -1;
	} else if (!sha1_hash_is_uptodate(sf)) {
		upload_send_error(u, 503, N_("SHA1 is being recomputed"));
		return -1;
	} else if (!upload_file_present(u, sf)) {
		goto not_found;
	}

	if (!upload_request_tth_matches(sf, tth)) {
		goto not_found;
	}

	upload_request_tth(sf);
	u->sf = shared_file_ref(sf);
	return 0;

malformed:
	if (GNET_PROPERTY(upload_debug)) {
		g_warning("malformed URN \"%s\" in /uri-res/N2R request sent by %s",
			NULL_STRING(uri), upload_host_info(u));
	}
	upload_error_remove(u, 400, N_("Malformed URN in /uri-res/N2R request"));
	return -1;

not_found:
	upload_error_not_found(u, uri);
	return -1;
}
