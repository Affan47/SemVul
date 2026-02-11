scgi_establish_connection(server *srv, handler_ctx *hctx) {
	struct sockaddr *scgi_addr;
	struct sockaddr_in scgi_addr_in;
#ifdef HAVE_SYS_UN_H
	struct sockaddr_un scgi_addr_un;
#endif
	socklen_t servlen;

	scgi_extension_host *host = hctx->host;
	scgi_proc *proc   = hctx->proc;
	int scgi_fd       = hctx->fd;

	memset(&scgi_addr, 0, sizeof(scgi_addr));

	if (!buffer_is_empty(proc->socket)) {
#ifdef HAVE_SYS_UN_H

		scgi_addr_un.sun_family = AF_UNIX;
		strcpy(scgi_addr_un.sun_path, proc->socket->ptr);
#ifdef SUN_LEN
		servlen = SUN_LEN(&scgi_addr_un);
#else

		servlen = proc->socket->used + sizeof(scgi_addr_un.sun_family);
#endif
		scgi_addr = (struct sockaddr *) &scgi_addr_un;
#else
		return -1;
#endif
	} else {
		scgi_addr_in.sin_family = AF_INET;
		if (0 == inet_aton(host->host->ptr, &(scgi_addr_in.sin_addr))) {
			log_error_write(srv, __FILE__, __LINE__, "sbs",
					"converting IP-adress failed for", host->host,
					"\nBe sure to specify an IP address here");

			return -1;
		}
		scgi_addr_in.sin_port = htons(proc->port);
		servlen = sizeof(scgi_addr_in);

		scgi_addr = (struct sockaddr *) &scgi_addr_in;
	}

	if (-1 == connect(scgi_fd, scgi_addr, servlen)) {
		if (errno == EINPROGRESS ||
		    errno == EALREADY ||
		    errno == EINTR) {
			if (hctx->conf.debug) {
				log_error_write(srv, __FILE__, __LINE__, "sd",
						"connect delayed, will continue later:", scgi_fd);
			}

			return 1;
		} else {
			log_error_write(srv, __FILE__, __LINE__, "sdsddb",
					"connect failed:", scgi_fd,
					strerror(errno), errno,
					proc->port, proc->socket);

			if (errno == EAGAIN) {


				log_error_write(srv, __FILE__, __LINE__, "s",
						"If this happend on Linux: You have been run out of local ports. "
						"Check the manual, section Performance how to handle this.");
			}

			return -1;
		}
	}
	if (hctx->conf.debug > 1) {
		log_error_write(srv, __FILE__, __LINE__, "sd",
				"connect succeeded: ", scgi_fd);
	}


	return 0;
}
