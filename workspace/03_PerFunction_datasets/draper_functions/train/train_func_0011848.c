child_read(struct archive_read_filter *self, char *buf, size_t buf_len)
{
	struct program_filter *state = self->data;
	ssize_t ret, requested, avail;
	const char *p;
#if defined(_WIN32) && !defined(__CYGWIN__)
	HANDLE handle = (HANDLE)_get_osfhandle(state->child_stdout);
#endif

	requested = buf_len > SSIZE_MAX ? SSIZE_MAX : buf_len;

	for (;;) {
		do {
#if defined(_WIN32) && !defined(__CYGWIN__)


			DWORD pipe_avail = -1;
			int cnt = 2;

			while (PeekNamedPipe(handle, NULL, 0, NULL,
			    &pipe_avail, NULL) != 0 && pipe_avail == 0 &&
			    cnt--)
				Sleep(5);
			if (pipe_avail == 0) {
				ret = -1;
				errno = EAGAIN;
				break;
			}
#endif
			ret = read(state->child_stdout, buf, requested);
		} while (ret == -1 && errno == EINTR);

		if (ret > 0)
			return (ret);
		if (ret == 0 || (ret == -1 && errno == EPIPE))


			return (child_stop(self, state));
		if (ret == -1 && errno != EAGAIN)
			return (-1);

		if (state->child_stdin == -1) {

			__archive_check_child(state->child_stdin,
			    state->child_stdout);
			continue;
		}


		p = __archive_read_filter_ahead(self->upstream, 1, &avail);
		if (p == NULL) {
			close(state->child_stdin);
			state->child_stdin = -1;
			fcntl(state->child_stdout, F_SETFL, 0);
			if (avail < 0)
				return (avail);
			continue;
		}

		do {
			ret = write(state->child_stdin, p, avail);
		} while (ret == -1 && errno == EINTR);

		if (ret > 0) {

			__archive_read_filter_consume(self->upstream, ret);
		} else if (ret == -1 && errno == EAGAIN) {

			__archive_check_child(state->child_stdin,
			    state->child_stdout);
		} else {

			close(state->child_stdin);
			state->child_stdin = -1;
			fcntl(state->child_stdout, F_SETFL, 0);


			if (ret == -1 && errno != EPIPE)
				return (-1);
		}
	}
}
