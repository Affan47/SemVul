mod_rrdtool_create_rrd(server *srv, plugin_data *p, plugin_config *s) {
	struct stat st;
	int r;


	if (0 == stat(s->path_rrd->ptr, &st)) {

		if (!S_ISREG(st.st_mode)) {
			log_error_write(srv, __FILE__, __LINE__, "sb",
					"not a regular file:", s->path_rrd);
			return HANDLER_ERROR;
		}


		if (st.st_size > 0) {
			return HANDLER_GO_ON;
		}
	}


	buffer_copy_string_len(p->cmd, CONST_STR_LEN("create "));
	buffer_append_string_buffer(p->cmd, s->path_rrd);
	buffer_append_string_len(p->cmd, CONST_STR_LEN(
		" --step 60 "
		"DS:InOctets:ABSOLUTE:600:U:U "
		"DS:OutOctets:ABSOLUTE:600:U:U "
		"DS:Requests:ABSOLUTE:600:U:U "
		"RRA:AVERAGE:0.5:1:600 "
		"RRA:AVERAGE:0.5:6:700 "
		"RRA:AVERAGE:0.5:24:775 "
		"RRA:AVERAGE:0.5:288:797 "
		"RRA:MAX:0.5:1:600 "
		"RRA:MAX:0.5:6:700 "
		"RRA:MAX:0.5:24:775 "
		"RRA:MAX:0.5:288:797 "
		"RRA:MIN:0.5:1:600 "
		"RRA:MIN:0.5:6:700 "
		"RRA:MIN:0.5:24:775 "
		"RRA:MIN:0.5:288:797\n"));

	if (-1 == (safe_write(p->write_fd, p->cmd->ptr, p->cmd->used - 1))) {
		log_error_write(srv, __FILE__, __LINE__, "ss",
			"rrdtool-write: failed", strerror(errno));

		return HANDLER_ERROR;
	}

	buffer_prepare_copy(p->resp, 4096);
	if (-1 == (r = safe_read(p->read_fd, p->resp->ptr, p->resp->size))) {
		log_error_write(srv, __FILE__, __LINE__, "ss",
			"rrdtool-read: failed", strerror(errno));

		return HANDLER_ERROR;
	}

	p->resp->used = r;

	if (p->resp->ptr[0] != 'O' ||
		p->resp->ptr[1] != 'K') {
		log_error_write(srv, __FILE__, __LINE__, "sbb",
			"rrdtool-response:", p->cmd, p->resp);

		return HANDLER_ERROR;
	}

	return HANDLER_GO_ON;
}
