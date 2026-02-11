build_doc_root(server *srv, connection *con, plugin_data *p, buffer *out, buffer *host) {
	stat_cache_entry *sce = NULL;

	buffer_prepare_copy(out, 128);

	if (p->conf.server_root->used) {
		buffer_copy_string_buffer(out, p->conf.server_root);

		if (host->used) {


			char *dp;

			BUFFER_APPEND_SLASH(out);

			if (NULL == (dp = strchr(host->ptr, ':'))) {
				buffer_append_string_buffer(out, host);
			} else {
				buffer_append_string_len(out, host->ptr, dp - host->ptr);
			}
		}
		BUFFER_APPEND_SLASH(out);

		if (p->conf.document_root->used > 2 && p->conf.document_root->ptr[0] == '/') {
			buffer_append_string_len(out, p->conf.document_root->ptr + 1, p->conf.document_root->used - 2);
		} else {
			buffer_append_string_buffer(out, p->conf.document_root);
			BUFFER_APPEND_SLASH(out);
		}
	} else {
		buffer_copy_string_buffer(out, con->conf.document_root);
		BUFFER_APPEND_SLASH(out);
	}

	if (HANDLER_ERROR == stat_cache_get_entry(srv, con, out, &sce)) {
		if (p->conf.debug) {
			log_error_write(srv, __FILE__, __LINE__, "sb",
					strerror(errno), out);
		}
		return -1;
	} else if (!S_ISDIR(sce->st.st_mode)) {
		return -1;
	}

	return 0;
}
