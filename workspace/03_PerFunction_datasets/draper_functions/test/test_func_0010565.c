netlink_parse_info(int (*filter) (struct sockaddr_nl *, struct nlmsghdr *),
		   nl_handle_t *nl, struct nlmsghdr *n)
{
	int status;
	int ret = 0;
	int error;

	while (1) {
		char buf[4096];
		struct iovec iov = { buf, sizeof buf };
		struct sockaddr_nl snl;
		struct msghdr msg =
		    { (void *) &snl, sizeof snl, &iov, 1, NULL, 0, 0 };
		struct nlmsghdr *h;

		status = recvmsg(nl->fd, &msg, 0);

		if (status < 0) {
			if (errno == EINTR)
				continue;
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				break;
			log_message(LOG_INFO, "Netlink: Received message overrun (%m)");
			continue;
		}

		if (status == 0) {
			log_message(LOG_INFO, "Netlink: EOF");
			return -1;
		}

		if (msg.msg_namelen != sizeof snl) {
			log_message(LOG_INFO,
			       "Netlink: Sender address length error: length %d",
			       msg.msg_namelen);
			return -1;
		}

		for (h = (struct nlmsghdr *) buf; NLMSG_OK(h, status);
		     h = NLMSG_NEXT(h, status)) {

			if (h->nlmsg_type == NLMSG_DONE)
				return ret;


			if (h->nlmsg_type == NLMSG_ERROR) {
				struct nlmsgerr *err = (struct nlmsgerr *) NLMSG_DATA(h);


				if (err->error == 0) {
					if (!(h->nlmsg_flags & NLM_F_MULTI))
						return 0;
					continue;
				}

				if (h->nlmsg_len < NLMSG_LENGTH(sizeof (struct nlmsgerr))) {
					log_message(LOG_INFO,
					       "Netlink: error: message truncated");
					return -1;
				}

				if (n && (err->error == -EEXIST) &&
				    ((n->nlmsg_type == RTM_NEWROUTE) ||
				     (n->nlmsg_type == RTM_NEWADDR)))
					return 0;

				log_message(LOG_INFO,
				       "Netlink: error: %s, type=(%u), seq=%u, pid=%d",
				       strerror(-err->error),
				       err->msg.nlmsg_type,
				       err->msg.nlmsg_seq, err->msg.nlmsg_pid);

				return -1;
			}


			if (nl != &nl_cmd && h->nlmsg_pid == nl_cmd.snl.nl_pid)
				continue;

			error = (*filter) (&snl, h);
			if (error < 0) {
				log_message(LOG_INFO, "Netlink: filter function error");
				ret = error;
			}
		}


		if (msg.msg_flags & MSG_TRUNC) {
			log_message(LOG_INFO, "Netlink: error: message truncated");
			continue;
		}
		if (status) {
			log_message(LOG_INFO, "Netlink: error: data remnant size %d",
			       status);
			return -1;
		}
	}

	return ret;
}
