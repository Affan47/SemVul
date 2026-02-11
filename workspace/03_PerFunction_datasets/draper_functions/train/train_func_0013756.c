_dessert_cli_logging_ringbuffer(struct cli_def *cli, char *command,
		char *argv[], int argc) {
	int newlen = -1;
	if (argc != 1 || (newlen = (int) strtol(argv[0], NULL, 10)) < 0) {
		cli_print(cli, "usage %s [buffer length]\n", command);
		return CLI_ERROR;
	}

	if (newlen == _dessert_logrbuf_len)
		return CLI_OK;

	if (newlen == 0) {
		cli_print(cli,
				"will not set buffer length to 0 - use no logging ringbuffer instead\n");
		return CLI_ERROR;
	}

	pthread_rwlock_wrlock(&_dessert_logrbuf_len_lock);


	if (newlen > _dessert_logrbuf_len) {
		_dessert_logrbuf = realloc(_dessert_logrbuf, newlen
				* DESSERT_LOGLINE_MAX * sizeof(char));
		if (_dessert_logrbuf == NULL) {
			_dessert_logrbuf_len = 0;
			_dessert_logrbuf_cur = 0;
		} else {
			_dessert_logrbuf_len = newlen;
		}
		dessert_logcfg(DESSERT_LOG_RBUF);

	} else if (newlen < _dessert_logrbuf_len) {

		if (_dessert_logrbuf_cur > newlen) {
			memmove(_dessert_logrbuf, _dessert_logrbuf + (DESSERT_LOGLINE_MAX
					* (_dessert_logrbuf_cur - newlen)), newlen
					* DESSERT_LOGLINE_MAX * sizeof(char));
			_dessert_logrbuf_cur -= newlen;
		}
		_dessert_logrbuf = realloc(_dessert_logrbuf, newlen
				* DESSERT_LOGLINE_MAX * sizeof(char));
		if (_dessert_logrbuf == NULL) {
			_dessert_logrbuf_len = 0;
			_dessert_logrbuf_cur = 0;
		} else {
			_dessert_logrbuf_len = newlen;
		}
	} else {
		dessert_err("this never happens");
	}
	if (_dessert_logrbuf_used > _dessert_logrbuf_len - 1)
		_dessert_logrbuf_used = _dessert_logrbuf_len - 1;
	pthread_rwlock_unlock(&_dessert_logrbuf_len_lock);
	return CLI_OK;

}
