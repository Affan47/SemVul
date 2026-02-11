parse_report(transport_smart *transport, git_push *push)
{
	git_pkt *pkt = NULL;
	const char *line_end = NULL;
	gitno_buffer *buf = &transport->buffer;
	int error, recvd;

	for (;;) {
		if (buf->offset > 0)
			error = git_pkt_parse_line(&pkt, buf->data,
						   &line_end, buf->offset);
		else
			error = GIT_EBUFS;

		if (error < 0 && error != GIT_EBUFS)
			return -1;

		if (error == GIT_EBUFS) {
			if ((recvd = gitno_recv(buf)) < 0)
				return recvd;

			if (recvd == 0) {
				giterr_set(GITERR_NET, "Early EOF");
				return -1;
			}
			continue;
		}

		gitno_consume(buf, line_end);

		error = 0;

		switch (pkt->type) {
			case GIT_PKT_DATA:

				error = add_push_report_sideband_pkt(push, (git_pkt_data *)pkt);
				break;
			case GIT_PKT_ERR:
				giterr_set(GITERR_NET, "report-status: Error reported: %s",
					((git_pkt_err *)pkt)->error);
				error = -1;
				break;
			case GIT_PKT_PROGRESS:
				if (transport->progress_cb) {
					git_pkt_progress *p = (git_pkt_progress *) pkt;
					error = transport->progress_cb(p->data, p->len, transport->message_cb_payload);
				}
				break;
			default:
				error = add_push_report_pkt(push, pkt);
				break;
		}

		git_pkt_free(pkt);


		if (error == GIT_ITEROVER)
			return 0;

		if (error < 0)
			return error;
	}
}
