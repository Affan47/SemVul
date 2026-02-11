lcp_options_init(struct ppp_lcp_t *lcp)
{
	struct lcp_option_t *lopt;
	struct lcp_option_handler_t *h;

	INIT_LIST_HEAD(&lcp->options);

	lcp->conf_req_len = sizeof(struct lcp_hdr_t);

	list_for_each_entry(h, &option_handlers, entry) {
		lopt = h->init(lcp);
		if (lopt) {
			lopt->h = h;
			list_add_tail(&lopt->entry, &lcp->options);
			lcp->conf_req_len += lopt->len;
		}
	}
}
