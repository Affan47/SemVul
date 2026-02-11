clean_logline(struct logline *lp)
{
	struct hdr *h, *h2;
#define freez(x) do { if (x) free(x); x = NULL; } while (0);
	freez(lp->df_H);
	freez(lp->df_U);
	freez(lp->df_q);
	freez(lp->df_b);
	freez(lp->df_h);
	freez(lp->df_m);
	freez(lp->df_s);
	freez(lp->df_u);
	freez(lp->df_ttfb);
	VTAILQ_FOREACH_SAFE(h, &lp->req_headers, list, h2) {
		VTAILQ_REMOVE(&lp->req_headers, h, list);
		freez(h->key);
		freez(h->value);
		freez(h);
	}
	VTAILQ_FOREACH_SAFE(h, &lp->resp_headers, list, h2) {
		VTAILQ_REMOVE(&lp->resp_headers, h, list);
		freez(h->key);
		freez(h->value);
		freez(h);
	}
	VTAILQ_FOREACH_SAFE(h, &lp->vcl_log, list, h2) {
		VTAILQ_REMOVE(&lp->vcl_log, h, list);
		freez(h->key);
		freez(h->value);
		freez(h);
	}
#undef freez
	memset(lp, 0, sizeof *lp);
}
