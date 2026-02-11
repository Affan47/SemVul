send_negotiate(mother, neg)
	const struct sockd_mother_t *mother;
	const struct sockd_negotiate_t *neg;
{
	const char *function = "send_negotiate()";
	struct iovec iovec[1];
	struct sockd_request_t req;
	int fdsendt, w;
	struct msghdr msg;
	CMSG_AALLOC(cmsg, sizeof(int));

#if HAVE_SENDMSG_DEADLOCK
	if (socks_lock(mother->lock, F_WRLCK, 0) != 0)
		return 1;
#endif


	sockshost2sockaddr(&neg->negstate.src, (struct sockaddr *)&req.from);
	req.req				= neg->req;
	req.rule				= neg->rule;
	req.state			= neg->state;
	req.state.command	= req.req.command;
	req.state.version	= req.req.version;


	sockshost2sockaddr(&neg->negstate.dst, (struct sockaddr *)&req.to);

	iovec[0].iov_base		= &req;
	iovec[0].iov_len		= sizeof(req);

	fdsendt = 0;

	CMSG_ADDOBJECT(neg->s, cmsg, sizeof(neg->s) * fdsendt++);

	msg.msg_iov				= iovec;
	msg.msg_iovlen			= ELEMENTS(iovec);
	msg.msg_name			= NULL;
	msg.msg_namelen		= 0;


	CMSG_SETHDR_SEND(msg, cmsg, sizeof(int) * fdsendt);

	slog(LOG_DEBUG, "sending request to mother");
	if ((w = sendmsg(mother->s, &msg, 0)) != sizeof(req))
		switch (errno) {
			case EAGAIN:
			case ENOBUFS:
				w = 1;
				break;

			default:
				swarn("%s: sendmsg(): %d of %d", function, w, sizeof(req));
		}

#if HAVE_SENDMSG_DEADLOCK
	socks_unlock(mother->lock);
#endif

	return w == sizeof(req) ? 0 : w;
}
