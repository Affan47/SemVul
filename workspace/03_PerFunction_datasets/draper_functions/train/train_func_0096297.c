read_cb(EV_P_ ev_io *w, int revents __attribute__((__unused__)))
{
	input_state *input = w->data;
	char *chunk;
	ssize_t n;

	do {
		if ((chunk = buffer_read_chunk(input->buffer, input->separator))
		    != NULL) {
			debug("Got complete chunk from standard input");
			ev_io_stop(EV_A_ w);
			input->read_handler(input, chunk);
			break;
		}
		if ((n = read(input->fd, input->input, sizeof(input->input)))
		    < 0) {
			if (errno == EAGAIN
#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
			    || errno == EWOULDBLOCK
#endif
			    || errno == EINTR)
				debug("Cannot read from standard input: %m");
			else
				die("Cannot read from standard input: %m");
		} else if (n == 0) {
			size_t len = buffer_size(input->buffer);

			debug("Got EOF from standard input");
			input->eof = true;
			if (len > 0) {
				debug("Providing the available data");
				ev_io_stop(EV_A_ w);
				chunk = xmalloc(len + 1);
				(void)buffer_read(input->buffer, chunk, len);
				chunk[len] = '\0';
				input->read_handler(input, chunk);
			} else {
				debug("No (more) data available");
				if (input->eof_handler != NULL)
					input->eof_handler(input);
				input_stop(input);
			}
		} else {
			debug("Got %zd bytes from standard input", n);
			buffer_append(input->buffer, input->input, (size_t)n);
		}
	} while (n > 0);
}
