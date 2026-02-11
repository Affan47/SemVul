ppp_chan_read(struct triton_md_handler_t *h)
{
	struct ppp_t *ppp = container_of(h, typeof(*ppp), chan_hnd);
	struct ppp_handler_t *ppp_h;
	uint16_t proto;

	while(1) {
cont:
		ppp->buf_size = read(h->fd, ppp->buf, PPP_MRU);
		if (ppp->buf_size < 0) {
			if (errno == EAGAIN)
				return 0;
			log_ppp_error("ppp_chan_read: %s\n", strerror(errno));
			return 0;
		}


		if (ppp->buf_size == 0) {
			ap_session_terminate(&ppp->ses, TERM_NAS_ERROR, 1);
			return 1;
		}

		if (ppp->buf_size < 2) {
			log_ppp_error("ppp_chan_read: short read %i\n", ppp->buf_size);
			continue;
		}

		proto = ntohs(*(uint16_t*)ppp->buf);
		list_for_each_entry(ppp_h, &ppp->chan_handlers, entry) {
			if (ppp_h->proto == proto) {
				ppp_h->recv(ppp_h);
				if (ppp->fd == -1) {

					return 1;
				}
				goto cont;
			}
		}

		lcp_send_proto_rej(ppp, proto);

	}
}
