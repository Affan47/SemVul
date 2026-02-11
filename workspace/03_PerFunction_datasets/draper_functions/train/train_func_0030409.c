cmd_read(struct bufferevent *buf_event, void *arg)
{
	struct cmdsocket *cmdsocket = (struct cmdsocket *)arg;
	char *cmdline;
	size_t len;
	int i;


	for(i = 0; i < 10 && !cmdsocket->shutdown; i++) {
		cmdline = evbuffer_readline(buf_event->input);
		if(cmdline == NULL) {

			break;
		}
		len = strlen(cmdline);

		INFO_OUT("Read a line of length %zd from client on fd %d: %s\n", len, cmdsocket->fd, cmdline);
		process_command(len, cmdline, cmdsocket);
		free(cmdline);
	}


	flush_cmdsocket(cmdsocket);
}
