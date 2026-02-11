unpack_new_headers(WSPMachine *sm, Octstr *hdrs) {
	List *new_headers;

	if (hdrs && octstr_len(hdrs) > 0) {
		new_headers = wsp_headers_unpack(hdrs, 0);
		if (sm->http_headers == NULL)
			sm->http_headers = http_create_empty_headers();
		http_header_combine(sm->http_headers, new_headers);
		return new_headers;
	}
	return NULL;
}
