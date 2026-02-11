send_echo_reply(struct ppp_lcp_t *lcp)
{
	struct lcp_hdr_t *hdr = (struct lcp_hdr_t*)lcp->ppp->buf;


	lcp->echo_sent = 0;
	lcp_update_echo_timer(lcp);

	hdr->code = ECHOREP;
	*(uint32_t *)(hdr + 1) = htonl(lcp->magic);

	if (conf_ppp_verbose)
		log_ppp_debug("send [LCP EchoRep id=%x <magic %08x>]\n", hdr->id, lcp->magic);

	ppp_chan_send(lcp->ppp, hdr, ntohs(hdr->len) + 2);
}
