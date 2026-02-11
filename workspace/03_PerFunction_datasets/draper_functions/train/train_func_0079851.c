fwlc_get_next_server(struct proxy *p, struct server *srvtoavoid)
{
	struct server *srv, *avoided;
	struct eb32_node *node;

	srv = avoided = NULL;

	if (p->srv_act)
		node = eb32_first(&p->lbprm.fwlc.act);
	else if (p->lbprm.fbck)
		return p->lbprm.fbck;
	else if (p->srv_bck)
		node = eb32_first(&p->lbprm.fwlc.bck);
	else
		return NULL;

	while (node) {


		struct server *s;

		s = eb32_entry(node, struct server, lb_node);
		if (!s->maxconn || (!s->nbpend && s->served < srv_dynamic_maxconn(s))) {
			if (s != srvtoavoid) {
				srv = s;
				break;
			}
			avoided = s;
		}
		node = eb32_next(node);
	}

	if (!srv)
		srv = avoided;

	return srv;
}
