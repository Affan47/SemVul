proc_open_buffer(const char *command, buffer *in, buffer *out, buffer *err) {
	proc_handler_t proc;

	if (proc_open(&proc, command) != 0) {
		return -1;
	}

	if (in) {
		if (write(proc.in.fd, (void *)in->ptr, in->used) < 0) {
			perror("error writing pipe");
			return -1;
		}
	}
	pipe_close(&proc.in);

	if (out) {
		proc_read_fd_to_buffer(proc.out.fd, out);
	}
	pipe_close(&proc.out);

	if (err) {
		proc_read_fd_to_buffer(proc.err.fd, err);
	} else {
		buffer *tmp = buffer_init();
		proc_read_fd_to_buffer(proc.err.fd, tmp);
		if (tmp->used > 0 &&  write(2, (void*)tmp->ptr, tmp->used) < 0) {
			perror("error writing pipe");
			return -1;
		}
		buffer_free(tmp);
	}
	pipe_close(&proc.err);

	proc_close(&proc);

	return 0;
}
