client_handle_client(struct lldpd *cfg,
    ssize_t(*send)(void *, int, void *, size_t),
    void *out,
    enum hmsg_type type, void *buffer, size_t n,
    int *subscribed)
{
	struct client_handle *ch;
	void *answer; ssize_t len, sent;

	log_debug("rpc", "handle client request");
	for (ch = client_handles; ch->handle != NULL; ch++) {
		if (ch->type == type) {
			TRACE(LLDPD_CLIENT_REQUEST(ch->name));
			answer = NULL;
			len  = ch->handle(cfg, &type, buffer, n, &answer,
			    subscribed);
			sent = send(out, type, answer, len);
			free(answer);
			return sent;
		}
	}

	log_warnx("rpc", "unknown message request (%d) received",
	    type);
	return -1;
}
