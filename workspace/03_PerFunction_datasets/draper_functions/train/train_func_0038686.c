readline_file(auparse_state_t *au)
{
	ssize_t rc;
	char *p_last_char;
	size_t n = 0;

	if (au->cur_buf != NULL) {
		free(au->cur_buf);
		au->cur_buf = NULL;
	}
	if (au->in == NULL) {
		errno = EBADF;
		return -1;
	}
	if ((rc = getline(&au->cur_buf, &n, au->in)) <= 0) {


		free(au->cur_buf);
		au->cur_buf = NULL;


		if (feof(au->in)) {

			errno = 0;
			return -2;
		}

		return -1;
	}
	p_last_char = au->cur_buf + (rc-1);
	if (*p_last_char == '\n') {
		*p_last_char = 0;
	}

	errno = 0;
	return 1;
}
